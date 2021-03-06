#!/usr/bin/env python

#Copyright  2008, Meka Robotics
#All rights reserved.
#http://mekabot.com

#Redistribution and use in source and binary forms, with or without
#modification, are permitted. 


#THIS SOFTWARE IS PROVIDED BY THE Copyright HOLDERS AND CONTRIBUTORS
#"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
#FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
#Copyright OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING,
#BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
#ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#POSSIBILITY OF SUCH DAMAGE.

import time
import m3.toolbox as m3t
import m3.rt_proxy as m3p
import m3.humanoid 
import m3.hand
import m3.gui as m3g
import m3.trajectory as m3jt
import numpy as nu
import yaml

class M3Proc:
    def __init__(self):
        self.proxy = m3p.M3RtProxy()
        self.gui = m3g.M3Gui(stride_ms=50)
        
        
        
    def stop(self):
        self.proxy.stop()

    def start(self):
        # ######## Setup Proxy and Components #########################
        self.proxy.start()
        self.current_first = True

        
        bot_name=m3t.get_robot_name()
        if bot_name == "":
            print 'Error: no robot components found:', bot_names
            return
        self.bot=m3.humanoid.M3Humanoid(bot_name)    
        arm_names = self.bot.get_available_chains()    
        arm_names = [x for x in arm_names if x.find('arm')!=-1]
        if len(arm_names)==0:
            print 'No arms found'
            return
        if len(arm_names)==1:
            self.arm_name=arm_names[0]
        else:
            self.arm_name = m3t.user_select_components_interactive(arm_names,single=True)[0]

        # ####### Setup Hand #############
        hand_names = self.bot.get_available_chains()    
        hand_names = [x for x in hand_names if x.find('hand')!=-1]
        if len(hand_names)==0:
            print 'No hands found'
            return
        if len(arm_names)==1:
            self.hand_name=hand_names[0]
        else:
            self.hand_name = m3t.user_select_components_interactive(hand_names,single=True)[0]
        # ####### Setup Proxy #############
        self.proxy.subscribe_status(self.bot)
        self.proxy.publish_command(self.bot)
        self.proxy.make_operational_all()
        self.bot.set_motor_power_on()
        self.ndof=self.bot.get_num_dof(self.arm_name)
        
        humanoid_shm_names=self.proxy.get_available_components('m3humanoid_shm')
        if len(humanoid_shm_names) > 0:
          self.proxy.make_safe_operational(humanoid_shm_names[0])


        
        self.via_traj={}
        self.via_traj_first=True
        self.theta_curr = [0.0]*self.ndof
        # ######## Square/Circle stuff #########################
        if self.arm_name == 'right_arm':
            self.center = [0.450, -0.28, -0.1745]                
        else:
            self.center = [0.450, 0.28, -0.1745]        
        avail_chains = self.bot.get_available_chains()
        for c in avail_chains:
            if c == 'torso':
                self.center[2] += 0.5079

        self.jt = m3jt.JointTrajectory(7)
        self.axis_demo = [0, 0, 1]

        # ##### Generate square vias ############################
        '''ik_vias=[]
        length_m = 25/ 100.0
        resolution = 20
        y_left = self.center[1] + length_m/2.0
        y_right = self.center[1] - length_m/2.0
        z_top = self.center[2] + length_m/2.0
        z_bottom = self.center[2] - length_m/2.0
        dy = (y_left - y_right) / nu.float(resolution)
        dz = (z_top - z_bottom) / nu.float(resolution)
        x = self.center[0]
        if self.arm_name=='right_arm':
            # first add start point
            ik_vias.append([x, y_left, z_top, self.axis_demo[0], self.axis_demo[1], self.axis_demo[2]])
            # add top line
            for i in range(resolution):                
                ik_vias.append([x, y_left - (i+1)*dy, z_top, self.axis_demo[0],self.axis_demo[1], self.axis_demo[2]])
            # add right line
            for i in range(resolution):                
                ik_vias.append([x, y_right, z_top - (i+1)*dz, self.axis_demo[0], self.axis_demo[1], self.axis_demo[2]])
            # add bottom line
            for i in range(resolution):                
                ik_vias.append([x, y_right + (i+1)*dy, z_bottom, self.axis_demo[0], self.axis_demo[1], self.axis_demo[2]])
            # add left line
            for i in range(resolution):                
                ik_vias.append([x, y_left, z_bottom + (i+1)*dz, self.axis_demo[0], self.axis_demo[1], self.axis_demo[2]])
        else:
            # first add start point
            ik_vias.append([x, y_right, z_top, self.axis_demo[0], self.axis_demo[1], self.axis_demo[2]])
            # add top line
            for i in range(resolution):                
                ik_vias.append([x, y_right + (i+1)*dy, z_top, self.axis_demo[0],self.axis_demo[1], self.axis_demo[2]])
            # add right line
            for i in range(resolution):                
                ik_vias.append([x, y_left, z_top - (i+1)*dz, self.axis_demo[0], self.axis_demo[1], self.axis_demo[2]])
            # add bottom line
            for i in range(resolution):                
                ik_vias.append([x, y_left - (i+1)*dy, z_bottom, self.axis_demo[0], self.axis_demo[1], self.axis_demo[2]])
            # add left line
            for i in range(resolution):                
                ik_vias.append([x, y_right, z_bottom + (i+1)*dz, self.axis_demo[0], self.axis_demo[1], self.axis_demo[2]])
        self.via_traj['Square']=[]
        # use zero position as reference for IK solver
        self.bot.set_theta_sim_deg(self.arm_name,[0]*self.bot.get_num_dof(self.arm_name))
        for ikv in ik_vias:
            theta_soln = []                    
            #print 'solving for square ik via:', ikv
            if self.bot.get_tool_axis_2_theta_deg_sim(self.arm_name, ikv[:3], ikv[3:], theta_soln):                    
                self.via_traj['Square'].append(theta_soln)
                self.bot.set_theta_sim_deg(self.arm_name,theta_soln)
            else:
                print 'WARNING: no IK solution found for via ', ikv
        self.bot.set_theta_sim_deg(self.arm_name,[0]*self.bot.get_num_dof(self.arm_name))
'''
        # ##### Generate circle vias ############################
        ik_vias=[]
        diameter_m = 25.0 / 100.0
        resolution = 40
        x = self.center[0]
        for i in range(resolution*4 + 1):
            dt = 2*nu.pi/(nu.float(resolution)*4)
            t = (nu.pi/2) + i*dt
            if t > nu.pi:
                t -= 2*nu.pi
            y = self.center[1] + (diameter_m/2.0) * nu.cos(t)
            z = self.center[2] + (diameter_m/2.0) * nu.sin(t)
            ik_vias.append([x, y, z, self.axis_demo[0], self.axis_demo[1], self.axis_demo[2]])
        self.via_traj['Circle']=[]
        # use zero position as reference for IK solver
        self.bot.set_theta_sim_deg(self.arm_name,[0]*self.bot.get_num_dof(self.arm_name))
        for ikv in ik_vias:
            theta_soln = []                    
            if self.bot.get_tool_axis_2_theta_deg_sim(self.arm_name, ikv[:3], ikv[3:], theta_soln):                    
                self.via_traj['Circle'].append(theta_soln)
                self.bot.set_theta_sim_deg(self.arm_name,theta_soln)
            else:
                print 'WARNING: no IK solution found for via ', ikv
        self.bot.set_theta_sim_deg(self.arm_name,[0]*self.bot.get_num_dof(self.arm_name))                

        # ##### Load Via Trajectories ############################
        self.via_files={'TrajA':'kha1.via'}
        for k in self.via_files.keys():
            fn=m3t.get_animation_file(self.via_files[k])
            print "Loading:",fn
            try:
                with open(fn,'r') as f:
                    d=yaml.safe_load(f.read())
                    self.via_traj[k]=d[self.arm_name]
            except IOError:
                print 'Via file',k,'not present. Skipping...'

        # ##### Hand Trajectories ############################
        if self.hand_name is not None:
            try:
                with open(m3t.get_animation_file(self.hand_name+'_postures.yml'),'r') as f:
                    self.hand_data= yaml.safe_load(f.read())
            except Exception,e:
                print e
        self.hand_traj_first=True
        # ######## Demo and GUI #########################
        self.off=False
        self.grasp=False
        self.arm_mode_names=['Off','Zero','Current','HoldUp','Circle','TrajA','Gravity']
        self.hand_mode_names=['Off','Open','Grasp','Animation']
        self.arm_mode_methods=[self.step_off,self.step_zero,self.step_current,self.step_hold_up,self.step_via_traj,
                       self.step_via_traj,self.step_gravity]
        self.hand_mode_methods=[self.step_hand_off,self.step_hand_open,self.step_hand_grasp,self.step_hand_animation]
        self.arm_mode=[0]
        self.hand_mode=[0]
        self.poses={'zero':  {'right_arm':[0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],'left_arm':[0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]},
                'holdup':{'right_arm':[56.0, 26.0, -8.0, 84.0, 119.0, -36.0, 2.0],'left_arm':[56.0, -26.0, 8.0, 84.0, -119.0, -36.0, -2.0]}}        
        self.stiffness=[85]
        self.velocity=[25]
        self.gui.add('M3GuiModes',  'Arm Mode',      (self,'arm_mode'),range(1),[self.arm_mode_names,1],m3g.M3GuiWrite,column=1)
        self.gui.add('M3GuiToggle', 'ESTOP', (self,'off'),[],[['Arm Enabled','Arm Disabled']],m3g.M3GuiWrite,column=1)
        if self.hand_name:
              self.gui.add('M3GuiToggle', 'Grasp', (self,'grasp'),[],[['GraspOpen','GraspClosed']],m3g.M3GuiWrite,column=1)
              self.gui.add('M3GuiModes',  'Hand Mode',      (self,'hand_mode'),range(1),[self.hand_mode_names,1],m3g.M3GuiWrite,column=1)
        self.gui.add('M3GuiSliders','Stiffness ', (self,'stiffness'),[0],[1,100],m3g.M3GuiWrite,column=1) 
        self.gui.add('M3GuiSliders','Velocity ', (self,'velocity'),[0],[0,40],m3g.M3GuiWrite,column=1) 
        self.gui.start(self.step)

    def get_arm_mode_name(self):
        return self.arm_mode_names[self.arm_mode[0]]

    def get_hand_mode_name(self):
        return self.hand_mode_names[self.hand_mode[0]]

    def get_stiffness(self):
        return [self.stiffness[0]/100.0]*self.ndof

    def step(self):
        try:
            self.proxy.step()
            print self.bot.get_timestamp_uS()
            print 'Arm: ',self.bot.get_theta_deg(self.arm_name)
            print 'Hand:',self.bot.get_theta_deg(self.hand_name)
            apply(self.arm_mode_methods[self.arm_mode[0]])
            if self.get_arm_mode_name()!='Square' and self.get_arm_mode_name()!='Circle' and self.get_arm_mode_name()!='TrajA':
                self.via_traj_first=True
            if self.get_arm_mode_name()!='Current':
                self.current_first=True
    
            if self.hand_name is not None:
                #print 'Hand',self.get_hand_mode_name()
                if self.get_hand_mode_name()!='Animation':
                    self.hand_traj_first=True
                apply(self.hand_mode_methods[self.hand_mode[0]])
        except Exception,e:
            print e
        #self.proxy.step()

    def step_hand_off(self):
        
        self.bot.set_mode_off(self.hand_name)

    def step_hand_open(self):
        self.bot.set_stiffness(self.hand_name,[0.8]*5)
        self.bot.set_mode_theta_gc(self.hand_name,[1,2,3,4])
        self.bot.set_mode_theta(self.hand_name,[0])
        self.bot.set_slew_rate_proportion(self.hand_name,[1.0]*5)
        self.bot.set_theta_deg(self.hand_name,[0.0]*5)

    def step_hand_grasp(self):
        
        self.bot.set_stiffness(self.hand_name,[0.8]*5)
        self.bot.set_slew_rate_proportion(self.hand_name,[1.0]*5)
        if self.grasp:
            self.bot.set_mode_theta(self.hand_name,[0])
            self.bot.set_mode_torque_gc(self.hand_name,[1,2,3,4])
            self.bot.set_torque(self.hand_name,[280.0]*4,[1,2,3,4])
            self.bot.set_theta_deg(self.hand_name,[90.0],[0])
        else:
            self.bot.set_mode_theta(self.hand_name,[0])
            self.bot.set_mode_theta_gc(self.hand_name,[1,2,3,4])
            self.bot.set_theta_deg(self.hand_name,[90.0,0.0,0.0,0.0,0.0])

    def step_hand_animation(self):
        
        self.bot.set_mode_splined_traj_gc(self.hand_name,[1,2,3,4])
        self.bot.set_mode_splined_traj(self.hand_name,[0])
        self.bot.set_stiffness(self.hand_name,[0.8]*5)
        self.bot.set_slew_rate_proportion(self.hand_name,[1.0]*5)
        if self.hand_traj_first:
            self.hand_traj_first=False
            for pose_name in self.hand_data['postures'].HoldUpkeys():
                theta_des=self.hand_data['postures'][pose_name]
                thetadot_avg=self.hand_data['thetadot_avg'][pose_name]
                self.bot.add_splined_traj_via_deg(self.hand_name,theta_des,thetadot_avg)
                self.bot.add_splined_traj_via_deg(self.hand_name,self.hand_data['param']['posture_return'],self.hand_data['param']['posture_return_speed'])
        if  self.bot.is_splined_traj_complete(self.hand_name):
            self.hand_traj_first=True

    def step_via_traj(self):
        self.bot.set_mode_splined_traj_gc(self.arm_name)
        self.bot.set_stiffness(self.arm_name, self.get_stiffness())
        self.bot.set_slew_rate_proportion(self.arm_name,[1.0]*self.ndof)
        if self.via_traj_first and len(self.via_traj[self.get_arm_mode_name()]):
            self.via_traj_first=False
            theta_0 = self.bot.get_theta_deg(self.arm_name)[:]            
            #vias = [list(theta_0)]+self.via_traj[self.get_arm_mode_name()]+[list(theta_0)] #start and stop at current pos
            vias = [list(theta_0)]+self.via_traj[self.get_arm_mode_name()] #start current pos
            idx = 0
            for v in vias:
                self.bot.add_splined_traj_via_deg(self.arm_name, v,[self.velocity[0]]*self.ndof)
                idx += 1
        if  self.bot.is_splined_traj_complete(self.arm_name):
            self.via_traj_first = True
            self.via_traj_redo = True

    def step_current(self):
        if self.current_first:
            self.current_first=False
            self.theta_curr = self.bot.get_theta_deg(self.arm_name)[:]            
        self.bot.set_mode_theta_gc(self.arm_name)
        self.bot.set_theta_deg(self.arm_name,self.theta_curr)
        self.bot.set_stiffness(self.arm_name,self.get_stiffness())
        #self.bot.set_thetadot_deg(self.arm_name,[20.0]*self.ndof)
        self.bot.set_slew_rate_proportion(self.arm_name,[1.0]*self.ndof)
        

    def step_zero(self):
        self.bot.set_mode_theta_gc(self.arm_name)
        self.bot.set_theta_deg(self.arm_name,self.poses['zero'][self.arm_name])
        self.bot.set_stiffness(self.arm_name,self.get_stiffness())
        #self.bot.set_thetadot_deg(self.arm_name,[20.0]*self.ndof)
        self.bot.set_slew_rate_proportion(self.arm_name,[1.0]*self.ndof)

    def step_hold_up(self):
        self.bot.set_mode_theta_gc(self.arm_name)
        self.bot.set_theta_deg(self.arm_name,self.poses['holdup'][self.arm_name])
        self.bot.set_stiffness(self.arm_name,self.get_stiffness())
        self.bot.set_slew_rate_proportion(self.arm_name,[1.0]*self.ndof)
        #self.bot.set_thetadot_deg(self.arm_name,[15.0]*self.ndof)

    def step_gravity(self):
        self.bot.set_mode_theta_gc(self.arm_name)
        #self.bot.set_theta_deg(self.arm_name,self.bot.get_theta_deg(self.arm_name))
        self.bot.set_theta_deg(self.arm_name,[0.0]*3,[4,5,6])
        self.bot.set_stiffness(self.arm_name,[0.0]*4,[0,1,2,3])
        self.bot.set_stiffness(self.arm_name,[0.7]*3,[4,5,6])
        self.bot.set_slew_rate_proportion(self.arm_name,[1.0]*7)
        return True
        
        
    def step_off(self):
        self.bot.set_mode_off(self.arm_name)



if __name__ == '__main__':
    t=M3Proc()
    try:
        t.start()
    except (KeyboardInterrupt,EOFError):
        pass
    t.stop()





