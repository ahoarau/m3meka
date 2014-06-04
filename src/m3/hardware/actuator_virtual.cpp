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

#include "m3/hardware/actuator_virtual.h"
#include "m3rt/base/m3rt_def.h"
#include "m3rt/base/component_factory.h"


namespace m3{
	
using namespace m3rt;
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void M3ActuatorVirtual::Startup()
{
	SetStateSafeOp();
}

/*void M3ActuatorVirtual::Shutdown()
{

}*/

bool M3ActuatorVirtual::ReadConfig(const char * filename)
{
	int val;
	//YAML::Node doc;
	if (!M3Actuator::ReadConfig(filename))
		return false;
	//GetYamlDoc(filename, doc);
	doc["joint_component"] >> jnt_name;
	// Set Order
	ParamThetaDf()->set_order(angle_df.GetXdf()->GetOrder());
	ParamThetaDotDf()->set_order(angle_df.GetXdotdf()->GetOrder());
	ParamThetaDotDotDf()->set_order(angle_df.GetXdotdotdf()->GetOrder());
	
	// Set N
	ParamThetaDf()->set_n(angle_df.GetXdf()->GetN());
	ParamThetaDotDf()->set_n(angle_df.GetXdotdf()->GetN());
	ParamThetaDotDotDf()->set_n(angle_df.GetXdotdotdf()->GetN());
	
	// Set Cutoff
	ParamThetaDf()->set_cutoff_freq(angle_df.GetXdf()->GetCutOffFreq());
	ParamThetaDotDf()->set_cutoff_freq(angle_df.GetXdotdf()->GetCutOffFreq());
	ParamThetaDotDotDf()->set_cutoff_freq(angle_df.GetXdotdotdf()->GetCutOffFreq());
	
	// Set Type
	ParamThetaDf()->set_type(angle_df.GetXdf()->GetType());
	ParamThetaDotDf()->set_type(angle_df.GetXdotdf()->GetType());
	ParamThetaDotDotDf()->set_type(angle_df.GetXdotdotdf()->GetType());
	
	
	return true;
}

bool M3ActuatorVirtual::LinkDependentComponents()
{
	joint=(M3Joint*) factory->GetComponent(jnt_name);
	if (joint==NULL)
	{
		M3_INFO("M3Joint component %s not found for component %s. Proceeding without it.\n",jnt_name.c_str(),GetName().c_str());
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void M3ActuatorVirtual::StepStatus()
{
	pnt_cnt++;
	
	if (IsStateError())
		return;

	
	status.set_flags(ACTUATOR_EC_FLAG_QEI_CALIBRATED);


	if (joint != NULL)
	{
		M3Transmission * t=joint->GetTransmission();
		if (t!=NULL)
		{
			
			//ParamThetaDotDf().cutoff_freq();
			
			// Set Order
			angle_df.GetXdf()->SetOrder(ParamThetaDf()->order());
			angle_df.GetXdotdf()->SetOrder(ParamThetaDotDf()->order());
			angle_df.GetXdotdotdf()->SetOrder(ParamThetaDotDotDf()->order());
			
			// Set N
			angle_df.GetXdf()->SetN(ParamThetaDf()->n());
			angle_df.GetXdotdf()->SetN(ParamThetaDotDf()->n());
			angle_df.GetXdotdotdf()->SetN(ParamThetaDotDotDf()->n());
			
			// Set Cutoff
			angle_df.GetXdf()->SetCutoff_freq(ParamThetaDf()->cutoff_freq());
			angle_df.GetXdotdf()->SetCutoff_freq(ParamThetaDotDf()->cutoff_freq());
			angle_df.GetXdotdotdf()->SetCutoff_freq(ParamThetaDotDotDf()->cutoff_freq());
			
			// Set Type
			angle_df.GetXdf()->SetType(ParamThetaDf()->type());
			angle_df.GetXdotdf()->SetType(ParamThetaDotDf()->type());
			angle_df.GetXdotdotdf()->SetType(ParamThetaDotDotDf()->type());
			
			// A.H : try to set fake torque to virtual motors = Tdes // TODO: investigate on torque jumps
			tq_sense.Step(this->GetDesiredTorque()-t->GetTorqueDesJoint()*1000.0/torque_shift);
			status.set_torque(tq_sense.GetTorque_mNm());
			status.set_torquedot(torquedot_df.Step(tq_sense.GetTorque_mNm()));
			// A.H test : torque and not torquedot (I don't care about torquedot)
			//status.set_torque(torquedot_df.Step(tq_jt));
			
			angle_df.Step(t->GetThetaDesJointDeg(),0); //Note: should be GetThetaDesSensorDeg, not working. this OK so long as all angle sensors are collocated 1:1
			status.set_theta(angle_df.GetTheta());
			status.set_thetadot(angle_df.GetThetaDot());
			status.set_thetadotdot(angle_df.GetThetaDotDot());
		}
		else
			M3_INFO("No transmission found for %s\n",joint->GetName().c_str());
	}
	//status.set_amp_temp(25.0);
	//status.set_current(0.0);
	//status.set_motor_temp(25.0);
}

void M3ActuatorVirtual::StepCommand()
{

}

}
