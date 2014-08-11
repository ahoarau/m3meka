#!/usr/bin/python
'''
Created on Apr 28, 2014

@author: Antoine Hoarau (hoarau.robotics@gmail.com)
'''
import time
import m3.rt_proxy as m3p
import m3.humanoid as m3h
import m3.toolbox as m3t
if __name__ == '__main__':
    proxy = m3p.M3RtProxy()
    proxy.start()
    bot = m3h.M3Humanoid(m3t.get_robot_name())
    bot.initialize(proxy)
    proxy.step()
    start = time.time()
    cnt=0
    while 1:
        try:
            cnt=cnt+1
            elapsed = time.time()-start
            for chain in bot.get_available_chains():
            
            bot.set_mode_theta_gc('right_arm')
            bot.set_slew_rate_proportion('right_arm',[1.0]*7)
            bot.set_stiffness('right_arm', [1.0]*7)
            bot.set_theta_deg('right_arm', [0.0]*7)
            if(elapsed >= 1):
                start = time.time()
                print 'cnt:',cnt,'freq : ',cnt
                cnt=0
            proxy.step()
        except KeyboardInterrupt:
            break
    proxy.stop()
        
