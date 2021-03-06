/* 
M3 -- Meka Robotics Robot Components
Copyright (c) 2010 Meka Robotics
Author: edsinger@mekabot.com (Aaron Edsinger)

M3 is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

M3 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with M3.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "m3/hardware/joint_virtual.h"
#include "m3rt/base/m3rt_def.h"
#include "m3rt/base/component_factory.h"
#include <cmath>

namespace m3{
	
using namespace m3rt;
using namespace std;
//#define MODE_SWITCH_SLEW_TIME 1.0 //Seconds
//Slew on joint desired when entering a mode
#define MODE_Q_ON_SLEW_TIME 1.0 
#define MODE_TQ_ON_SLEW_TIME 1.0 
#define MODE_PWM_ON_SLEW_TIME 1.0
#define MODE_BRAKE_OFF_SLEW_TIME 2.0


void M3JointVirtual::StepStatus()
{
	pnt_cnt++;
	if (IsStateError())
		return;
	status.set_flags(act->GetFlags());
	status.set_amp_temp(act->GetAmpTemp());
	status.set_motor_temp(act->GetMotorTemp());
	status.set_ambient_temp(act->GetAmbientTemp());
	status.set_case_temp(act->GetCaseTemp());
	status.set_power(act->GetPower());
	status.set_current(act->GetCurrent());
	status.set_pwm_cmd(act->GetPwmCmd());
	status.set_theta(trans->GetThetaJointDeg());
	status.set_thetadot(trans->GetThetaDotJointDeg());
	status.set_thetadotdot(trans->GetThetaDotDotJointDeg());
	status.set_torque(trans->GetTorqueJoint());  // TODO: Make GetTorque nNm again
	status.set_torquedot(trans->GetTorqueDotJoint());
	//status.set_torque_gravity(GetTorqueGravity());
}




void M3JointVirtual::StepCommand()
{
	if (!act || IsStateSafeOp())
		return;
	
	if (IsVersion(IQ) && !ctrl_simple)
		return;
	
	
	if(IsStateError())
	{
		if (IsVersion(IQ))
		ctrl_simple->SetDesiredControlMode(CTRL_MODE_OFF);
		else
		act->SetDesiredControlMode(ACTUATOR_MODE_OFF);
		
		return;
	}
	
	
	
	
	if (command.ctrl_mode() == JOINT_MODE_THETA && command.smoothing_mode() == SMOOTHING_MODE_MIN_JERK)
	{
	command.set_ctrl_mode(JOINT_MODE_THETA_MJ);
		
	}
	
	if (command.ctrl_mode() == JOINT_MODE_THETA_GC && command.smoothing_mode() == SMOOTHING_MODE_MIN_JERK)
	{
	command.set_ctrl_mode(JOINT_MODE_THETA_GC_MJ);	  
	}
	
	//Avoid pops
/*	if (command.ctrl_mode()!=mode_last)
	{
		q_on_slew.Reset(0.0);
		tq_on_slew.Reset(0.0);
		pwm_on_slew.Reset(0.0);
		q_slew.Reset(GetThetaDeg());
		jerk_joint.Startup(GetTimestamp(), GetThetaDeg());
		if (IsVersion(IQ)) 
		tq_switch=GetTorque()*1000;  // TODO: Make GetTorque nNm again
		else
		tq_switch=GetTorque(); 
		q_switch=GetThetaDeg();
		pwm_switch=GetPwmCmd();
		if (IsVersion(IQ)) { 
		ctrl_simple->ResetIntegrators();
		}
	}*/
	if (IsVersion(IQ)) { 
	if (!act->IsMotorPowerSlewedOn())
	ctrl_simple->ResetIntegrators();	 
	}
	
	
	if (IsVersion(IQ)) { 
	
		ctrl_simple->SetDesiredControlMode(CTRL_MODE_OFF);
		
		switch(command.ctrl_mode())
		{
			
			case JOINT_MODE_THETA:
			case JOINT_MODE_THETA_MJ:
			{
				if (!IsEncoderCalibrated())
				{
				// M3_INFO("Not calib %s\n",GetName().c_str());
				break;
				}
				CalcThetaDesiredSmooth();
				mReal des=trans->GetThetaDesActuatorDeg();
				StepBrake(des,trans->GetThetaActuatorDeg());
				//Do PID in actuator space so result is direct PWM
				//ctrl_simple->SetDesiredControlMode(CTRL_MODE_THETA);
				ctrl_simple->SetDesiredControlMode(CTRL_MODE_THETA);
				ctrl_simple->SetDesiredTheta(DEG2RAD(des));
				break;
			}
			case JOINT_MODE_THETA_GC:
			case JOINT_MODE_THETA_GC_MJ:
			case JOINT_MODE_POSE:
			{
				if (!IsEncoderCalibrated())
				break;
				mReal stiffness,gravity,tq_des;
				CalcThetaDesiredSmooth();
				mReal des=trans->GetThetaDesJointDeg();
				StepBrake(des,trans->GetThetaJointDeg());
				//Do PID in joint space
				if (command.ctrl_mode() == JOINT_MODE_POSE)
				{
				tq_des =pid_theta_gc.Step(trans->GetThetaJointDeg(),
						trans->GetThetaDotJointDeg(),
						des,
						0.0,
						0.0,
						param.kq_d_pose(),
						0.0,
						0.0);
				} else {
				tq_des =pid_theta_gc.Step(trans->GetThetaJointDeg(),
						trans->GetThetaDotJointDeg(),
						des,
						param.kq_p(),
						param.kq_i(),
						param.kq_d(),
						param.kq_i_limit(),
						param.kq_i_range());
				}
				/*if (pnt_cnt%200==0) {		
					M3_DEBUG("actuator: %s\n", GetName().c_str());
					M3_DEBUG("tq_des: %f\n",tq_des);
					M3_DEBUG("th: %f -> %f  thdot: %f\n",trans->GetThetaJointDeg(),des,trans->GetThetaDotJointDeg());
					M3_DEBUG("des: %f\n\n",des);
				}*/
				stiffness=CLAMP(command.q_stiffness(),0.0,1.0);
				gravity=GetTorqueGravity()*param.kq_g();
				//Ramp in from torque at switch-over point
				mReal tq_on, tq_out;
				tq_on=tq_on_slew.Step(1.0,1.0/MODE_TQ_ON_SLEW_TIME); 
				//tq_on = 1.0;
				tq_out=tq_on*(stiffness*tq_des-gravity)+(1.0-tq_on)*tq_switch;
				//tq_out = tq_switch;
				//tq_out = stiffness*tq_des-gravity;
				//Send out
				trans->SetTorqueDesJoint(tq_out/1000.0);	//TODO: convert back to mNm	
				
				ctrl_simple->SetDesiredControlMode(CTRL_MODE_TORQUE);
				ctrl_simple->SetDesiredTorque(trans->GetTorqueDesActuator());
				
				break;
			}
			case JOINT_MODE_TORQUE_GC:			
			{
				if (!IsEncoderCalibrated())
				break;	
				// A.H
				//Do PID in torque grav model space
				mReal tq_des =pid_tq_grav_model.Step(trans->GetTorqueJoint(),
						trans->GetTorqueDotJoint(),
						-GetTorqueGravity()+command.tq_desired(),
						param.kq_p_tq_gm(),
						param.kq_i_tq_gm(),
						param.kq_d_tq_gm(),
						param.kq_i_limit_tq_gm(),
						param.kq_i_range_tq_gm());
				//Ramp in from torque at switch-over point
				mReal tq_on, tq_out;
				tq_on=tq_on_slew.Step(1.0,1.0/MODE_TQ_ON_SLEW_TIME); 
				//tq_on = 1.0;
				tq_out=tq_on*(tq_des)+(1.0-tq_on)*tq_switch;				
				//Send out
				trans->SetTorqueDesJoint(tq_out/1000.0);	//TODO: convert back to mNm
				
				ctrl_simple->SetDesiredControlMode(CTRL_MODE_TORQUE);
				ctrl_simple->SetDesiredTorque(trans->GetTorqueDesActuator());
				
				tq_des = status.theta()-trans->GetTorqueDesJoint();
				// Let's transform to angle for the robot to move :)
				trans->SetThetaDesJointDeg(tq_des);
				break;
			}
			
			case JOINT_MODE_THETADOT_GC:			
			{
				if (!IsEncoderCalibrated())
				break;
				mReal stiffness,gravity,tq_des;
				//CalcThetaDesiredSmooth();
				trans->SetThetaDotDesJointDeg(command.qdot_desired());
				mReal des=trans->GetThetaDotDesJointDeg();
				//StepBrake(des,trans->GetThetaDotJointDeg());
				tq_des =pid_thetadot_gc.Step(trans->GetThetaDotJointDeg(),
						trans->GetThetaDotDotJointDeg(),
						des,
						param.kqdot_p(),
						param.kqdot_i(),
						param.kqdot_d(),
						param.kqdot_i_limit(),
						param.kqdot_i_range());
				StepBrake(tq_des,trans->GetTorqueJoint());
				stiffness=CLAMP(command.q_stiffness(),0.0,1.0);
				gravity=GetTorqueGravity()*param.kq_g();
				//Ramp in from torque at switch-over point
				mReal tq_on, tq_out;
				tq_on=tq_on_slew.Step(1.0,1.0/MODE_TQ_ON_SLEW_TIME); 
				tq_out=tq_on*(stiffness*tq_des-gravity)+(1.0-tq_on)*tq_switch;
				//tq_out = tq_switch;
				//tq_out = stiffness*tq_des-gravity;
				//Send out
				/*if (pnt_cnt%200==0) {		
					M3_DEBUG("actuator: %s\n", GetName().c_str());
					M3_DEBUG("tq_des: %f tqout_des: %f v: %f\n",tq_des,tq_out,trans->GetThetaDotJointDeg());
					M3_DEBUG("des: %f Tjoint: %f desac: %f\n\n",des,trans->GetTorqueJoint(),trans->GetTorqueDesActuator());
				}*/
				trans->SetTorqueDesJoint(tq_out/1000.0);	//TODO: convert back to mNm	
				
				ctrl_simple->SetDesiredControlMode(CTRL_MODE_TORQUE);
				ctrl_simple->SetDesiredTorque(trans->GetTorqueDesJoint());
				tq_des = status.theta()+trans->GetTorqueDesJoint();
				// Let's transform to angle for the robot to move :)
				trans->SetThetaDesJointDeg(tq_des);
				break;
			}

			case JOINT_MODE_THETADOT:			
			{
				if (!IsEncoderCalibrated())
				break;
				mReal stiffness,gravity,tq_des;
				//CalcThetaDesiredSmooth();
				trans->SetThetaDotDesJointDeg(command.qdot_desired());
				mReal des=trans->GetThetaDotDesJointDeg();
				//StepBrake(des,trans->GetThetaDotJointDeg());
				tq_des =pid_thetadot_gc.Step(trans->GetThetaDotJointDeg(),
						trans->GetThetaDotDotJointDeg(),
						des,
						param.kqdot_p(),
						param.kqdot_i(),
						param.kqdot_d(),
						param.kqdot_i_limit(),
						param.kqdot_i_range());
				StepBrake(tq_des,trans->GetTorqueJoint());
				stiffness=CLAMP(command.q_stiffness(),0.0,1.0);
				//Ramp in from torque at switch-over point
				mReal tq_on, tq_out;
				tq_on=tq_on_slew.Step(1.0,1.0/MODE_TQ_ON_SLEW_TIME); 
				tq_out=tq_on*(stiffness*tq_des)+(1.0-tq_on)*tq_switch;
				//Send out
				if (pnt_cnt%200==0) {		
					M3_DEBUG("actuator: %s\n", GetName().c_str());
					M3_DEBUG("tq_des: %f tqout_des: %f v: %f\n",tq_des,tq_out,trans->GetThetaDotJointDeg());
					M3_DEBUG("des: %f Tjoint: %f desac: %f\n\n",des,trans->GetTorqueJoint(),trans->GetTorqueDesActuator());
				}
				trans->SetTorqueDesJoint(tq_out/1000.0);	//TODO: convert back to mNm	
				
				ctrl_simple->SetDesiredControlMode(CTRL_MODE_TORQUE);
				ctrl_simple->SetDesiredTorque(trans->GetTorqueDesActuator());
				tq_des = status.theta()+trans->GetTorqueDesJoint();
				// Let's transform to angle for the robot to move :)
				trans->SetThetaDesJointDeg(tq_des);
				break;
			}
			case JOINT_MODE_TORQUE:
			{	
				if (!IsEncoderCalibrated())
				break;	
				// A.H
				//Do PID in torque grav model space
				mReal tq_des =pid_tq_grav_model.Step(trans->GetTorqueJoint(),
						trans->GetTorqueDotJoint(),
						command.tq_desired(),
						param.kq_p_tq_gm(),
						param.kq_i_tq_gm(),
						param.kq_d_tq_gm(),
						param.kq_i_limit_tq_gm(),
						param.kq_i_range_tq_gm());
				//Ramp in from torque at switch-over point
				mReal tq_on, tq_out;
				tq_on=tq_on_slew.Step(1.0,1.0/MODE_TQ_ON_SLEW_TIME); 
				//tq_on = 1.0;
				tq_out=tq_on*(tq_des)+(1.0-tq_on)*tq_switch;				
				//Send out
				trans->SetTorqueDesJoint(tq_out/1000.0);	//TODO: convert back to mNm
				
				ctrl_simple->SetDesiredControlMode(CTRL_MODE_TORQUE);
				ctrl_simple->SetDesiredTorque(trans->GetTorqueDesActuator());
				
				tq_des = status.theta()-trans->GetTorqueDesJoint();
				// Extra PId not really useful
				/*tq_des =pid_theta_gc.Step(trans->GetThetaJointDeg(),
						trans->GetThetaDotJointDeg(),
						status.theta()-tq_out,
						param.kq_p(),
						param.kq_i(),
						param.kq_d(),
						param.kq_i_limit(),
						param.kq_i_range());*/
				
				// Let's transform to angle for the robot to move :)
				trans->SetThetaDesJointDeg(tq_des);
				break;
			}
			case JOINT_MODE_TORQUE_GRAV_MODEL:
			{
				if (!IsEncoderCalibrated())
				break;
				
				mReal tq_des;				
								
				//Do PID in torque grav model space
				
				tq_des =pid_tq_grav_model.Step(GetTorqueGravity(),
						trans->GetThetaDotJointDeg(),
						-command.tq_desired(),
						param.kq_p_tq_gm(),
						param.kq_i_tq_gm(),
						param.kq_d_tq_gm(),
						param.kq_i_limit_tq_gm(),
						param.kq_i_range_tq_gm());
				
				
				
				//Ramp in from torque at switch-over point
				mReal tq_on, tq_out;
				tq_on=tq_on_slew.Step(1.0,1.0/MODE_TQ_ON_SLEW_TIME); 
				//tq_on = 1.0;
				tq_out=tq_on*(tq_des)+(1.0-tq_on)*tq_switch;				
				//Send out
				trans->SetTorqueDesJoint(tq_out/1000.0);	//TODO: convert back to mNm	
				
				ctrl_simple->SetDesiredControlMode(CTRL_MODE_CURRENT);
				ctrl_simple->SetDesiredTorque(trans->GetTorqueDesActuator());
				
				/*if (tmp_cnt++ == 1000)
				{
				M3_DEBUG("------------------------\n");
				M3_DEBUG("%s\n", GetName().c_str());
				M3_DEBUG("tq_gc: %f\n", GetTorqueGravity());
				//M3_DEBUG("tq_dot: %f\n", -trans->GetTorqueDotJoint());				    
				M3_DEBUG("tq_des: %f\n", tq_des);
				M3_DEBUG("tq_on: %f\n", tq_on);
				//M3_DEBUG("tq_switch: %f\n", tq_switch);
				M3_DEBUG("tq_out: %f\n", tq_out);				    
				M3_DEBUG("tq_act: %f\n", trans->GetTorqueDesActuator());
				tmp_cnt = 0;
				}*/
				
				break;
			}
			case JOINT_MODE_OFF:
			case JOINT_MODE_PWM:
			default:
				ctrl_simple->SetDesiredControlMode(CTRL_MODE_OFF);
				//act->SetDesiredControlMode(ACTUATOR_MODE_OFF);
				mReal des; //dummy
				StepBrake(des,0);
				break;	
		};
	} else { // Legacy, no supported on BMW,MAX2 versions 2.0
	
//		act->SetDesiredControlMode(ACTUATOR_MODE_OFF);//default
		
		switch(command.ctrl_mode())
		{
			case JOINT_MODE_PWM:
			{
				//Ramp in from pwm at switch-over point
				mReal pwm_des=command.pwm_desired();
				StepBrake(pwm_des,0);			
				//StepBrake(pwm_des,command.pwm_cmd());			
				
				mReal pwm_on, pwm_out;
				pwm_on=pwm_on_slew.Step(1.0,1.0/MODE_PWM_ON_SLEW_TIME);
				pwm_out=pwm_on*pwm_des+(1.0-pwm_on)*pwm_switch;
				//Send out
				act->SetDesiredControlMode(ACTUATOR_MODE_PWM);
				if (disable_pwm_ramp)
				act->SetDesiredPwm(command.pwm_desired());
				else
				act->SetDesiredPwm((int)pwm_out);;
				break;
			}
			case JOINT_MODE_THETA:
			case JOINT_MODE_THETA_MJ:
			{
				
				
					
				if (!IsEncoderCalibrated())
				{
//					M3_INFO("Not calib %s\n",GetName().c_str());
					break;
				}
				
				CalcThetaDesiredSmooth();
				mReal des=trans->GetThetaDesActuatorDeg();
				StepBrake(des,trans->GetThetaActuatorDeg());
				//Do PID in actuator space so result is direct PWM
				mReal pwm =pid_theta.Step(trans->GetThetaActuatorDeg(),
							trans->GetThetaDotActuatorDeg(),
							des,
							param.kt_p(),
							param.kt_i(),
							param.kt_d(),
							param.kt_i_limit(),
							param.kt_i_range());
				act->SetDesiredControlMode(ACTUATOR_MODE_PWM);
				//Ramp in from pwm at switch-over point
				mReal pwm_on, pwm_out;
				pwm_on=pwm_on_slew.Step(1.0,1.0/MODE_PWM_ON_SLEW_TIME);
				pwm_out=pwm_on*pwm+(1.0-pwm_on)*pwm_switch;
				act->SetDesiredPwm((int)pwm_out);
				/*if (tmp_cnt++%100==0)
				{
					M3_INFO("des %3.2f sen: %3.2f pid: %3.2f out: %3.2f\n",des,trans->GetThetaActuatorDeg(),
						pwm,pwm_out);
				}*/
				break;
			}
			case JOINT_MODE_THETA_GC:
			case JOINT_MODE_THETA_GC_MJ:
			{
				if (!IsEncoderCalibrated())
				break;
				mReal stiffness,gravity,tq_des;
				CalcThetaDesiredSmooth();
				mReal des=trans->GetThetaDesJointDeg();
				StepBrake(des,trans->GetThetaJointDeg());
				//Do PID in joint space
				tq_des =pid_theta_gc.Step(trans->GetThetaJointDeg(),
						trans->GetThetaDotJointDeg(),
						des,
						param.kq_p(),
						param.kq_i(),
						param.kq_d(),
						param.kq_i_limit(),
						param.kq_i_range());
				stiffness=CLAMP(command.q_stiffness(),0.0,1.0);
				gravity=GetTorqueGravity()*param.kq_g();
				//Ramp in from torque at switch-over point
				mReal tq_on, tq_out;
				tq_on=tq_on_slew.Step(1.0,1.0/MODE_TQ_ON_SLEW_TIME);
				tq_out=tq_on*(stiffness*tq_des-gravity)+(1.0-tq_on)*tq_switch;
				//Send out
				
				trans->SetTorqueDesJoint(tq_out);
				act->SetDesiredControlMode(ACTUATOR_MODE_TORQUE);
				act->SetDesiredTorque(trans->GetTorqueDesActuator());
				break;
			}
			case JOINT_MODE_TORQUE_GC:			
			{
			if (!IsEncoderCalibrated())
				break;
				mReal tq_on, tq_out,gravity;
				mReal tq_des=command.tq_desired();
				StepBrake(tq_des,trans->GetTorqueJoint());
				gravity=GetTorqueGravity()*param.kq_g();
				//Ramp in from torque at switch-over point
				tq_on=tq_on_slew.Step(1.0,1.0/MODE_TQ_ON_SLEW_TIME);
				tq_out=tq_on*(tq_des-gravity)+(1.0-tq_on)*tq_switch;
				//Send out
				trans->SetTorqueDesJoint(tq_out);
				act->SetDesiredControlMode(ACTUATOR_MODE_TORQUE);

				act->SetDesiredTorque(trans->GetTorqueDesActuator());
				break;
			}
			case JOINT_MODE_TORQUE:
			{		  
				mReal tq_on,tq_out;
				//Ramp in from torque at switch-over point
				mReal tq_des=command.tq_desired();
				
				StepBrake(tq_des,trans->GetTorqueJoint());
				tq_on=tq_on_slew.Step(1.0,1.0/MODE_TQ_ON_SLEW_TIME);
				tq_out=tq_on*tq_des+(1.0-tq_on)*tq_switch;
				//Send out
				trans->SetTorqueDesJoint(tq_out);
				act->SetDesiredControlMode(ACTUATOR_MODE_TORQUE);
				act->SetDesiredTorque(trans->GetTorqueDesActuator());			
				
				/*if (tmp_cnt++ == 100)
				{
				M3_DEBUG("tq_des: %f\n", tq_des);
				M3_DEBUG("tq_on: %f\n", tq_on);
				M3_DEBUG("tq_switch: %f\n", tq_switch);
				M3_DEBUG("tq_out: %f\n", tq_out);				    
				M3_DEBUG("tq_act: %f\n", trans->GetTorqueDesActuator());
				tmp_cnt = 0;
				}*/
				break;
			}
			case JOINT_MODE_OFF:
			default:
				act->SetDesiredControlMode(ACTUATOR_MODE_OFF);
				mReal des; //dummy
				StepBrake(des,0);
				break;
		};
	}
	
	mode_last=(int)command.ctrl_mode();
	
	/*if (tmp_cnt == 100)
	{
	M3_DEBUG("tq_out: %f\n", ((M3ActuatorCommand*)act->GetCommand())->tq_desired() );
	
	tmp_cnt = 0;
	}*/
	
}


}

