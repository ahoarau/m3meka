# -*- coding: utf-8 -*-
#Copyright  2010, Meka Robotics
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

import copy
import config_toolbox as ct

# ########################## ACTUATOR_EC A2.R3.J0-J6 ########################################

config_arm_a1r1_actuator_ec={
    'chid': 0,
    'ethercat': {'pdo_version': 'actx1_pdo_v1',
                 'product_code': 1001,
                 'serial_number': 0},
    'name': 'm3actuator_ec_xxx_j0',
    'version':'default',
    'firmware': 'm3_controller_sea_a1r1',
    'param': {'config': 2,
              'k_d': 0,
              'k_d_shift': 0,
              'k_ff': 0,
              'k_ff_shift': 0,
              'k_ff_zero': 0,
              'k_i': 0,
              'k_i_limit': 0,
              'k_i_shift': 0,
              'k_p': 0,
              'k_p_shift': 0,
              'pwm_db': 0,
              'pwm_max': 3186,
              'qei_max': 0,
              'qei_min': 0,
              't_max': 4096,
              't_min': 0},
    'pwr_component': 'm3pwr_pwr000'}

config_arm_a1r1_actuator_ec_j0=copy.deepcopy(config_arm_a1r1_actuator_ec)
config_arm_a1r1_actuator_ec_j1=copy.deepcopy(config_arm_a1r1_actuator_ec)
config_arm_a1r1_actuator_ec_j2=copy.deepcopy(config_arm_a1r1_actuator_ec)
config_arm_a1r1_actuator_ec_j3=copy.deepcopy(config_arm_a1r1_actuator_ec)
config_arm_a1r1_actuator_ec_j4=copy.deepcopy(config_arm_a1r1_actuator_ec)
config_arm_a1r1_actuator_ec_j5=copy.deepcopy(config_arm_a1r1_actuator_ec)
config_arm_a1r1_actuator_ec_j6=copy.deepcopy(config_arm_a1r1_actuator_ec)

# ########################## ACTUATOR A2.R3.J0-J1 ########################################

config_arm_a1r1_actuator_j0={
    'calib': {'amp_temp': {'cb_bias': 0.0,
                           'cb_mV_at_25C': 750.0,
                           'cb_mV_per_C': 10.0,
                           'cb_scale': 1.0,
                           'name': 'Microchip TC1047',
                           'type': 'adc_linear_5V'},
              'angle_df': {'theta_df': {'cutoff_freq': 80,
                                        'order': 3,
                                        'type': 'butterworth'},
                           'thetadot_df': {'cutoff_freq': 20,
                                           'order': 3,
                                           'type': 'diff_butterworth'},
                           'thetadotdot_df': {'cutoff_freq': 20,
                                              'order': 3,
                                              'type': 'diff_butterworth'},
                           'type': 'df_chain'},
              'current': {'cb_bias': 0.0,
                          'cb_mV_per_A': 66.0,
                          'cb_scale': 1.0,
                          'cb_ticks_at_zero_a': 2048,
                          'cb_ticks_at_zero_b': 2048,
                          'name': 'Allegro ACS712-30',
                          'type': 'adc_linear_5V'},
              'motor': {'model_type': 'model_v1',
                        'temp_sensor_type': 'ambient',
                        'current_sensor_type': 'measured',
                        'name': 'Maxon RE40 150W 24V 14887',
                        'nominal_voltage':24.0, #V
                        'no_load_speed':7580.0, #rpm
                        'no_load_current': 137.0, #mA
                        'nominal_speed': 6930.0, #rpm
                        'nominal_torque': 170.0, #mNm
                        'nominal_current': 5.77, #A
                        'stall_torque': 2280.0, #mNm
                        'starting_current':75.7, #A
                        'max_efficiency': 91.0, #%
                        'winding_resistance': 0.317,#Ohm
                        'winding_inductance': .0823,#mH
                        'torque_constant': 30.2,#mNm/A
                        'speed_constant':317.0,#rpm/V
                        'speed_torque_gradient':3.33,#rpm/mNm
                        'mechanical_time_constant':4.81,#ms
                        'rotor_inertia': 138,#gcm^2
                        'thermal_resistance_housing_ambient': 4.65,#K/W
                        'thermal_resistance_rotor_housing': 1.93,#K/W
                        'thermal_time_constant_winding': 41.6,#s
                        'thermal_time_constant_motor': 1120.0,#s
                        'max_winding_temp': 155.0,#C
                        'gear_ratio':120.0,
                        'amplifier_resistance':0.0136,#Ohm
                        'max_pwm_duty':3186.0,
                        'safe_thermal_pct': 0.90,
                        'i_scale': 1.1
                        },
              'ext_temp': {'cb_bias': 0.0,
                             'cb_mV_at_25C': 750.0,
                             'cb_mV_per_C': 10.0,
                             'cb_scale': 1.0,
                             'name': 'Analog TMP36',
                             'type': 'adc_linear_3V3'},
              'theta': {'cb_bias': 0.0,
                        'cb_scale': 1.0,
                        'cb_theta':[0.087890625,0],
                        'name': 'US Digital MA13',
                        'type': 'ma3_12bit_poly'},
              'torque': {'cb_bias': 0.0,
                         'cb_inv_torque': [1.0,0.0],
                         'cb_scale': 1.0,
                         'cb_torque': [1.0,0.0],
                         'name': 'ContElec VertX13',
                         'type': 'sea_vertx_14bit'},
              'torquedot_df': {'cutoff_freq': 100,
                               'order': 3,
                               'type': 'diff_butterworth'}},
    'description': 'max2_v0.2_seax2_v1.2',
    'ec_component': 'm3actuator_ec_xxx_jx',
    'ignore_bounds': 0,
    'safe_pwm_limit': 1,
    'joint_component': 'm3joint_xxx_jx',
    'name': 'm3actuator_xxx_jx',
    'version':'iss',
    'param': {'max_overload_time': 3.0,
              'max_amp_temp': 125.0,
              'max_amp_current': 20000.0,
              'max_tq': 40000.0,
              'min_tq': -40000.0}}

config_arm_a1r1_actuator_j1=copy.deepcopy(config_arm_a1r1_actuator_j0)
config_arm_a1r1_actuator_j1['calib']['motor']['gear_ratio']=100.0

# ########################## ACTUATOR A2.R3.J2-J3 ########################################

config_arm_a1r1_actuator_j2={
    'calib': {'amp_temp': {'cb_bias': 0.0,
                           'cb_mV_at_25C': 750.0,
                           'cb_mV_per_C': 10.0,
                           'cb_scale': 1.0,
                           'name': 'Microchip TC1047',
                           'type': 'adc_linear_5V'},
              'angle_df': {'theta_df': {'cutoff_freq': 80,
                                        'order': 3,
                                        'type': 'butterworth'},
                           'thetadot_df': {'cutoff_freq': 20,
                                           'order': 3,
                                           'type': 'diff_butterworth'},
                           'thetadotdot_df': {'cutoff_freq': 20,
                                              'order': 3,
                                              'type': 'diff_butterworth'},
                           'type': 'df_chain'},
              'current': {'cb_bias': 0.0,
                          'cb_mV_per_A': 66.0,
                          'cb_scale': 1.0,
                          'cb_ticks_at_zero_a': 2048,
                          'cb_ticks_at_zero_b': 2048,
                          'name': 'Allegro ACS712-30',
                          'type': 'adc_linear_5V'},
              'motor': {'model_type': 'model_v1',
                        'temp_sensor_type': 'ambient',
                        'current_sensor_type': 'none',
                        'name': 'Maxon EC45 Flat 50W 24V 339286',
                        'nominal_voltage':24.0, #V
                        'no_load_speed':4700.0, #rpm
                        'no_load_current': 116.0, #mA
                        'nominal_speed': 3410.0, #rpm
                        'nominal_torque': 64.2, #mNm
                        'nominal_current': 1.32, #A
                        'stall_torque': 337.0, #mNm
                        'starting_current':7.10, #A
                        'max_efficiency': 77.0, #%
                        'winding_resistance': 3.38,#Ohm
                        'winding_inductance': 1.15,#mH
                        'torque_constant': 47.5,#mNm/A
                        'speed_constant':201.0,#rpm/V
                        'speed_torque_gradient':14.3,#rpm/mNm
                        'mechanical_time_constant':20.3,#ms
                        'rotor_inertia': 135,#gcm^2
                        'thermal_resistance_housing_ambient': 4.25,#K/W
                        'thermal_resistance_rotor_housing': 4.5,#K/W
                        'thermal_time_constant_winding': 16.6,#s
                        'thermal_time_constant_motor': 212.0,#s
                        'max_winding_temp': 125.0,#C
                        'gear_ratio':100.0,
                        'amplifier_resistance':0.0136,#Ohm
                        'max_pwm_duty':3186.0,
                        'safe_thermal_pct': 0.90,
                        'i_scale': 1.1
                        },
              'ext_temp': {'cb_bias': 0.0,
                             'cb_mV_at_25C': 750.0,
                             'cb_mV_per_C': 10.0,
                             'cb_scale': 1.0,
                             'name': 'Analog TMP36',
                             'type': 'adc_linear_3V3'},
              'theta': {'cb_bias': 0.0,
                        'cb_scale': 1.0,
                        'cb_theta':[0.087890625,0],
                        'name': 'US Digital MA13',
                        'type': 'ma3_12bit_poly'},
              'torque': {'cb_bias': 0.0,
                         'cb_inv_torque': [1.0,0.0],
                         'cb_scale': 1.0,
                         'cb_torque': [1.0,0.0],
                         'name': 'ContElec VertX13',
                         'type': 'sea_vertx_14bit'},
              'torquedot_df': {'cutoff_freq': 100,
                               'order': 3,
                               'type': 'diff_butterworth'}},
    'description': 'max2_v0.2_seax2_v1.2',
    'ec_component': 'm3actuator_ec_xxx_jx',
    'ignore_bounds': 0,
    'safe_pwm_limit': 1,
    'joint_component': 'm3joint_xxx_jx',
    'name': 'm3actuator_xxx_jx',
    'version':'iss',
    'param': {'max_overload_time': 1.0,
              'max_amp_temp': 125.0,
              'max_amp_current': 20000.0,
              'max_tq': 20000.0,
              'min_tq': -20000.0}}

config_arm_a1r1_actuator_j3=config_arm_a1r1_actuator_j2

# ########################## ACTUATOR A2.R3.J4 ########################################

config_arm_a1r1_actuator_j4={
    'calib': {'amp_temp': {'type': 'temp_25C'},
              'angle_df': {'theta_df': {'cutoff_freq': 80,
                                        'order': 3,
                                        'type': 'butterworth'},
                           'thetadot_df': {'cutoff_freq': 20,
                                           'order': 3,
                                           'type': 'diff_butterworth'},
                           'thetadotdot_df': {'cutoff_freq': 20,
                                              'order': 3,
                                              'type': 'diff_butterworth'},
                           'type': 'df_chain'},
              'current': {'type': 'none'},
              'motor': {'model_type': 'model_v1',
                        'temp_sensor_type': 'ambient',
                        'current_sensor_type': 'none',
                        'name': 'Maxon EC32 Flat 15W 24V 267121',
                        'nominal_voltage':24.0, #V
                        'no_load_speed':4390.0, #rpm
                        'no_load_current': 73.4, #mA
                        'nominal_speed': 2800.0, #rpm
                        'nominal_torque': 23.2, #mNm
                        'nominal_current': 0.490, #A
                        'stall_torque': 85.0, #mNm
                        'starting_current':1.75, #A
                        'max_efficiency': 64.0, #%
                        'winding_resistance': 13.7,#Ohm
                        'winding_inductance': 7.73,#mH
                        'torque_constant': 49.0,#mNm/A
                        'speed_constant':195.0,#rpm/V
                        'speed_torque_gradient':54.5,#rpm/mNm
                        'mechanical_time_constant':20.0,#ms
                        'rotor_inertia': 35.0,#gcm^2
                        'thermal_resistance_housing_ambient': 9.74,#K/W
                        'thermal_resistance_rotor_housing': 4.63,#K/W
                        'thermal_time_constant_winding': 8.1,#s
                        'thermal_time_constant_motor': 108.0,#s
                        'max_winding_temp': 125.0,#C
                        'gear_ratio':100.0,
                        'amplifier_resistance':0.019,#Ohm
                        'max_pwm_duty':3186.0,
                        'safe_thermal_pct': 0.90,
                        'i_scale': 1.1
                        },
              'ext_temp': {'cb_bias': 0.0,
                             'cb_mV_at_25C': 750.0,
                             'cb_mV_per_C': 10.0,
                             'cb_scale': 1.0,
                             'name': 'Analog TMP36',
                             'type': 'adc_linear_3V3'},
              'theta': {'cb_bias': 0.0,
                        'cb_scale': 1.0,
                        'cb_theta':[0.087890625,0],
                        'name': 'US Digital MA13',
                        'type': 'ma3_12bit_poly'},
              'torque': {'cb_bias': 0.0,
                         'cb_inv_torque': [1.0,0.0],
                         'cb_scale': 1.0,
                         'cb_torque': [1.0,0.0],
                         'name': 'ContElec VertX13',
                         'type': 'sea_vertx_14bit'},
              'torquedot_df': {'cutoff_freq': 100,
                               'order': 3,
                               'type': 'diff_butterworth'}},
    'description': 'bmw_v0.3',
    'ec_component': 'm3actuator_ec_xxx_jx',
    'ignore_bounds': 0,
    'safe_pwm_limit': 1,
    'version':'iss',
    'joint_component': 'm3joint_xxx_jx',
    'name': 'm3actuator_xxx_jx',
    'param': {'max_overload_time': 3.0,
              'max_amp_temp': 100.0,
              'max_amp_current': 8800.0,
              'max_tq': 4000.0,
              'min_tq': -4000.0}}

config_arm_a1r1_actuator_j5=copy.deepcopy(config_arm_a1r1_actuator_j4)
config_arm_a1r1_actuator_j6=copy.deepcopy(config_arm_a1r1_actuator_j4)
config_arm_a1r1_actuator_j5['calib']['motor']['gear_ratio']=59.5238
config_arm_a1r1_actuator_j6['calib']['motor']['gear_ratio']=59.5238

# ########################## JOINT A2.R3.J0-J4 ########################################

config_arm_a1r1_joint_j0={
    'actuator_component': 'm3actuator_xxx_j0', 
    'name': 'm3joint_xxx_j0',
    'version':'iss',
    'brake': 'none',
    'param': {'kq_d': 0.0,
              'kq_g': 1.0,
              'kq_i': 0.0,
              'kq_i_limit': 0.0,
              'kq_i_range': 0.0,
              'kq_p': 0.0,
              'kt_d': 0.0,
              'kt_i': 0.0,
              'kt_i_limit': 0.0,
              'kt_i_range': 0.0,
              'kt_p': 0.0,
              'max_q': 360.0,
              'max_q_pad': 0.0,
              'max_q_slew_rate': 25.0,
              'min_q': 0.0,
              'min_q_pad': 0.0},
    'transmission':{'act_name': 'm3actuator_xxx_j0',
                    'qj_to_qa':[1.0],
                    'qs_to_qj':[1.0],
                    'tqj_to_tqa':[1.0],
                    'tqs_to_tqj':[1.0],
                    'type': 'gear'}}

config_arm_a1r1_joint_j1=config_arm_a1r1_joint_j0
config_arm_a1r1_joint_j2=config_arm_a1r1_joint_j0
config_arm_a1r1_joint_j3=config_arm_a1r1_joint_j0
config_arm_a1r1_joint_j4=config_arm_a1r1_joint_j0

# ########################## JOINT A2.R3.J5 ########################################

config_arm_a1r1_joint_j5={
    'actuator_component': 'm3actuator_xxx_j5', 
    'name': 'm3joint_xxx_j0',
    'version':'iss',
    'brake': 'none',
    'param': {'kq_d': 0.0,
              'kq_g': 1.0,
              'kq_i': 0.0,
              'kq_i_limit': 0.0,
              'kq_i_range': 0.0,
              'kq_p': 0.0,
              'kt_d': 0.0,
              'kt_i': 0.0,
              'kt_i_limit': 0.0,
              'kt_i_range': 0.0,
              'kt_p': 0.0,
              'max_q': 360.0,
              'max_q_pad': 0.0,
              'max_q_slew_rate': 25.0,
              'min_q': 0.0,
              'min_q_pad': 0.0},
    'transmission':{'act_name': 'm3actuator_xxx_j5',
                    'cpj_name': 'm3joint_xxx_j6',
                    'qj_to_qa':[1.1905,1.1905],
                    'qs_to_qj':[1.0,0.0],
                    'tqj_to_tqa':[0.42,0.42],
                    'tqs_to_tqj':[1.1905,1.1905],
                    'type': 'differential'}}

# ########################## JOINT A2.R3.J6 ########################################

config_arm_a1r1_joint_j6={
    'actuator_component': 'm3actuator_xxx_j6', 
    'name': 'm3joint_xxx_j0',
    'version':'iss',
    'brake': 'none',
    'param': {'kq_d': 0.0,
              'kq_g': 1.0,
              'kq_i': 0.0,
              'kq_i_limit': 0.0,
              'kq_i_range': 0.0,
              'kq_p': 0.0,
              'kt_d': 0.0,
              'kt_i': 0.0,
              'kt_i_limit': 0.0,
              'kt_i_range': 0.0,
              'kt_p': 0.0,
              'max_q': 360.0,
              'max_q_pad': 0.0,
              'max_q_slew_rate': 25.0,
              'min_q': 0.0,
              'min_q_pad': 0.0},
    'transmission':{'act_name': 'm3actuator_xxx_j6',
                    'cpj_name': 'm3joint_xxx_j5',
                    'qj_to_qa':[-1.1905,1.1905],
                    'qs_to_qj':[1.0,0.0],
                    'tqj_to_tqa':[-0.42,0.42],
                    'tqs_to_tqj':[-1.1905,1.1905],
                    'type': 'differential'}}

# ########################## ARM A2.R3 ########################################

config_arm_a1r1={
    'name': 'm3arm_xxx',
    'ndof': 7,
    'limb_name': 'xxx_arm',
    'version':'iss',
    'dynamatics_component': 'm3dynamatics_xxx',
'joint_components':{'J0': 'm3joint_xxx_j0',
                    'J1': 'm3joint_xxx_j1',
                    'J2': 'm3joint_xxx_j2',
                    'J3': 'm3joint_xxx_j3',
                    'J4': 'm3joint_xxx_j4',
                    'J5': 'm3joint_xxx_j5',
                    'J6': 'm3joint_xx_j6'}}

# ########################## Dynamatics Right Arm A2.R3 ########################################



a1r1_dynamatics_right_arm={
    'chain_component': 'm3arm_xxx',
    'links': [{'Ixx': 0.00681123,#
               'Ixy': 0.00000279,#
               'Ixz': -0.00000096,#
               'Iyy': 0.00461596,#
               'Iyz': 0.00015180,#
               'Izz': 0.003267,#
               'a': 0.0,#
               'alpha': 90.0,#
               'cx': 0.00001331,#
               'cy': -0.01280796,#
               'cz': -0.02663968,#
               'd': 0.18465,#
               'joint_offset': -90,#
               'm': 2.031},#
              {'Ixx': 0.00195358,#
               'Ixy': -0.00077554,#
               'Ixz': 0.00000439,#
               'Iyy': 0.00121948,#
               'Iyz': 0.00000474,#
               'Izz': 0.0021736,#
               'a': 0.0,#
               'alpha': 90,#
               'cx':  0.02634954,#
               'cy': -0.04305855,#
               'cz': -0.00080890,#
               'd': 0.0,#
               'joint_offset': 90.0,#
               'm': 0.566},# 
              {'Ixx': 0.02949661,#
               'Ixy': 0.00008636,#
               'Ixz': -0.00242880,#
               'Iyy':  0.02983326,#
               'Iyz': -0.00013024,#
               'Izz': 0.00244235,#
               'a': 0.03175,#
               'alpha': 90.0,#
               'cx': 0.01015213,#
               'cy': -0.00013272,#
               'cz': -0.08417638,#
               'd': 0.27857,#
               'joint_offset': 90.0,#
               'm': 2.296},# 
              {'Ixx': 0.00062344,#
               'Ixy': 0.00000002,#
               'Ixz': 0.00000000,#
               'Iyy': 0.00042457,#
               'Iyz': 0.00001768,#
               'Izz': 0.00038623,#
               'a': -0.00502,#
               'alpha': 90,#
               'cx': 0.00000214,#
               'cy': 0.02612472,#
               'cz': -0.00027814,#
               'd': 0,#
               'joint_offset': 0.0,#
               'm': 0.223},#
              {'Ixx': 0.03130809,#
               'Ixy': -0.00000289,#
               'Ixz': -0.00089153,#
               'Iyy': 0.03135827,#
               'Iyz': -0.00003896,#
               'Izz': 0.00120798,#
               'a': 0.0,#
               'alpha': -90,#
               'cx': 0.00455921,#
               'cy': -0.00050523,#
               'cz': -0.13310851,#
               'd': 0.27747,#
               'joint_offset': 0,
               'm': 1.473},#
              {'Ixx': 0.00011597,#?
               'Ixy': -0.00000005,#?
               'Ixz': 0.00000004,#?
               'Iyy': 0.00011378,#?
               'Iyz': -0.00000012,#?
               'Izz': 0.00007497,#?
               'a': 0.0,#
               'alpha': 90,#
               'cx': 0.00002303,#?
               'cy': -0.00160400,#?
               'cz': -0.00174552,#?
               'd': 0.0,#
               'joint_offset': 90.0,#
               'm': 0.241},#?
              {'Ixx':0.00009428,#?
               'Ixy': 0.00000002,#?
               'Ixz': 0.00000000,#?
               'Iyy': 0.00006133,#?
               'Iyz': -0.00000074,#?
               'Izz': 0.00005054,#?
               'a': 0.0,#
               'alpha': 90.0,#
               'cx': -0.00000535,#?
               'cy': -0.01052783,#?
               'cz': 0.00356904,#?
               'd': 0.0,#
               'joint_offset': 90.0,#
               'm': 0.090},#
              {'a': 0.0,#
               'alpha': 90.0,#
               'd': 0.04414,#
               'joint_offset': 0.0}],#
    'name': 'm3dynamatics_xxx',
    'version':'iss',
    'ndof': 7,
    'param': {'payload_com': [0.0, 0.0, 0.0],
              'payload_inertia': [0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
              'payload_mass': 0.0,
              'use_accelerations': False,
              'use_velocities': False}}
   
# ########################## Dynamatics Left Arm A2.R3 ########################################

a1r1_dynamatics_left_arm={
    'chain_component': 'm3arm_xxx',
    'links': [{'Ixx': 0.00681105,#
               'Ixy': 0.00000121,#
               'Ixz': 0.00000385,#
               'Iyy': 0.00461590,#
               'Iyz': -0.00015183,#
               'Izz': 0.00326738,#
               'a': 0.0,#
               'alpha': 90.0,#
               'cx': 0.00004773,#
               'cy': -0.01280850,#
               'cz': 0.02663942,#
               'd': -0.18465,#
               'joint_offset': -90,#
               'm': 2.031},#
              {'Ixx': 0.00195361,#
               'Ixy': 0.00077561,#
               'Ixz': -0.00001340,#
               'Iyy': 0.00121961,#
               'Iyz': -0.00001596,#
               'Izz':  0.00217371,#
               'a': 0.0,#
               'alpha': 90,#
               'cx': -0.02635253,#
               'cy': -0.04305754,#
               'cz': -0.00030161,#
               'd': 0.0,#
               'joint_offset': 90.0,#
               'm': 0.566},#        
              {'Ixx': 0.02947222,#
               'Ixy': -0.00008909,#
               'Ixz': -0.00241841,#
               'Iyy': 0.02980912,#
               'Iyz': 0.00013713,#
               'Izz': 0.00244260,#
               'a': -0.03175,#
               'alpha': 90.0,#
               'cx': 0.01014779,#
               'cy': 0.00011326,#
               'cz': -0.08411111,#
               'd': 0.27857,#
               'joint_offset': 90.0,#
               'm': 2.296},#
              {'Ixx': 0.00062344,#
               'Ixy': -0.00000002,#
               'Ixz': 0.00000000,#
               'Iyy':0.00042457,#
               'Iyz': -0.00001768,#
               'Izz': 0.00038623,#
               'a': -0.00502,#
               'alpha': 90,#
               'cx': -0.00000214,#
               'cy': 0.02612472,#
               'cz': 0.00027814,#
               'd': 0,#
               'joint_offset': 0.0,#
               'm': 0.223},#
              {'Ixx': 0.03130809,#
               'Ixy': -0.00000289,#
               'Ixz': -0.00089153,#
               'Iyy': 0.03135827,#
               'Iyz': -0.00003896,#
               'Izz': 0.00120798,#
               'a': 0.0,#
               'alpha': -90,#
               'cx': 0.00455921,#
               'cy': -0.00050523,#
               'cz': -0.13310851,#
               'd': 0.27747,#
               'joint_offset': 0,
               'm': 1.473},#
              {'Ixx': 0.00011597,#?
               'Ixy': -0.00000005,#?
               'Ixz': 0.00000004,#?
               'Iyy': 0.00011378,#?
               'Iyz': -0.00000012,#?
               'Izz': 0.00007497,#?
               'a': 0.0,#
               'alpha': 90,#
               'cx': 0.00002303,#?
               'cy': -0.00160400,#?
               'cz': -0.00174552,#?
               'd': 0.0,#
               'joint_offset': 90.0,#
               'm': 0.241},#?
              {'Ixx':0.00009428,#?
               'Ixy': 0.00000002,#?
               'Ixz': 0.00000000,#?
               'Iyy': 0.00006133,#?
               'Iyz': -0.00000074,#?
               'Izz': 0.00005054,#?
               'a': 0.0,#
               'alpha': 90.0,#
               'cx': -0.00000535,#?
               'cy': -0.01052783,#?
               'cz': 0.00356904,#?
               'd': 0.0,#
               'joint_offset': 90.0,#
               'm': 0.090},#
              {'a': 0.0,#
               'alpha': 90.0,#
               'd': 0.04414,#
               'joint_offset': 0.0}],#
    'name': 'm3dynamatics_xxx',
    'version':'iss',
    'ndof': 7,
    'param': {'payload_com': [0.0, 0.0, 0.0],
              'payload_inertia': [0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
              'payload_mass': 0.0,
              'use_accelerations': False,
              'use_velocities': False}}
   
# ########################## Payloads A2.R3 ########################################

#Inertia: Ixx, Ixy, Ixz, Iyy, Iyz, Izz
a1r1_payload_right_h2r3_fts={
    'payload_com': [-0.00286004, 0.00206754, 0.06242752],#
    'payload_inertia': [0.00484971, #
                        -0.00003507, #
                        0.00007626, #
                        0.00507558, #
                        0.00009209, #
                        0.00080672],#
    'payload_mass': 0.838#
    }

#Inertia: Ixx, Ixy, Ixz, Iyy, Iyz, Izz
a1r1_payload_left_h2r3_fts={
    'payload_com': [0.00358036, 0.00184370, 0.06227732],#
    'payload_inertia': [0.00479873,#
                         0.00008313,#
                         0.00008839,#
                         0.00510505,#
                         0.00007973,#
                         0.00081578],#
    'payload_mass': 0.834#
    }

#Inertia: Ixx, Ixy, Ixz, Iyy, Iyz, Izz
a1r1_payload_right_h2r3={
    'payload_com': [-0.00286004, 0.00206754, 0.06242752],#
    'payload_inertia': [0.00484971, #
                        -0.00003507, #
                        0.00007626, #
                        0.00507558, #
                        0.00009209, #
                        0.00080672],#
    'payload_mass': 0.838#
    }

#Inertia: Ixx, Ixy, Ixz, Iyy, Iyz, Izz
a1r1_payload_left_h2r3={
    'payload_com': [0.00358036, 0.00184370, 0.06227732],#
    'payload_inertia': [0.00479873,#
                         0.00008313,#
                         0.00008839,#
                         0.00510505,#
                         0.00007973,#
                         0.00081578],#
    'payload_mass': 0.834#
    }
#Inertia: Ixx, Ixy, Ixz, Iyy, Iyz, Izz
a1r1_payload_g1r1_fts={
    'payload_com': [0.0, 0.0, 0.0],
    'payload_inertia': [0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    'payload_mass': 0.0
    }

#Inertia: Ixx, Ixy, Ixz, Iyy, Iyz, Izz
a1r1_payload_g1r1={
    'payload_com': [0.0, 0.0, 0.0],
    'payload_inertia': [0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    'payload_mass': 0.0
    }

#Inertia: Ixx, Ixy, Ixz, Iyy, Iyz, Izz
a1r1_payload_none={
    'payload_com': [0.0, 0.0, 0.0],
    'payload_inertia': [0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    'payload_mass': 0.0
    }

#Graspers w/FTS
a1r1_dynamatics_right_h2r3_fts=copy.deepcopy(a1r1_dynamatics_right_arm)
a1r1_dynamatics_left_h2r3_fts=copy.deepcopy(a1r1_dynamatics_left_arm)
a1r1_dynamatics_right_g1r1_fts=copy.deepcopy(a1r1_dynamatics_right_arm)
a1r1_dynamatics_left_g1r1_fts=copy.deepcopy(a1r1_dynamatics_left_arm)
ct.set_payload(a1r1_dynamatics_right_h2r3_fts, a1r1_payload_right_h2r3_fts)
ct.set_payload(a1r1_dynamatics_left_h2r3_fts, a1r1_payload_left_h2r3_fts)
ct.set_payload(a1r1_dynamatics_right_g1r1_fts, a1r1_payload_g1r1_fts)
ct.set_payload(a1r1_dynamatics_left_g1r1_fts, a1r1_payload_g1r1_fts)

#Graspers w/o FTS
a1r1_dynamatics_right_h2r3=copy.deepcopy(a1r1_dynamatics_right_arm)
a1r1_dynamatics_left_h2r3=copy.deepcopy(a1r1_dynamatics_left_arm)
a1r1_dynamatics_right_g1r1=copy.deepcopy(a1r1_dynamatics_right_arm)
a1r1_dynamatics_left_g1r1=copy.deepcopy(a1r1_dynamatics_left_arm)
ct.set_payload(a1r1_dynamatics_right_h2r3, a1r1_payload_right_h2r3)
ct.set_payload(a1r1_dynamatics_left_h2r3, a1r1_payload_left_h2r3)
ct.set_payload(a1r1_dynamatics_right_g1r1, a1r1_payload_g1r1)
ct.set_payload(a1r1_dynamatics_left_g1r1, a1r1_payload_g1r1)

#No Grasper
a1r1_dynamatics_right=copy.deepcopy(a1r1_dynamatics_right_arm)
a1r1_dynamatics_left=copy.deepcopy(a1r1_dynamatics_left_arm)
ct.set_payload(a1r1_dynamatics_right, a1r1_payload_none)
ct.set_payload(a1r1_dynamatics_left, a1r1_payload_none)

# ########################## A2.R3 ########################################

config_full_a1r1={'actuator_ec':[config_arm_a1r1_actuator_ec_j0,
                                 config_arm_a1r1_actuator_ec_j1,
                                 config_arm_a1r1_actuator_ec_j2,
                                 config_arm_a1r1_actuator_ec_j3,
                                 config_arm_a1r1_actuator_ec_j4,
                                 config_arm_a1r1_actuator_ec_j5,
                                 config_arm_a1r1_actuator_ec_j6],
                  'actuator':[config_arm_a1r1_actuator_j0,
                              config_arm_a1r1_actuator_j1,
                              config_arm_a1r1_actuator_j2,
                              config_arm_a1r1_actuator_j3,
                              config_arm_a1r1_actuator_j4,
                              config_arm_a1r1_actuator_j5,
                              config_arm_a1r1_actuator_j6],
                  'joint':[config_arm_a1r1_joint_j0,
                           config_arm_a1r1_joint_j1,
                           config_arm_a1r1_joint_j2,
                           config_arm_a1r1_joint_j3,
                           config_arm_a1r1_joint_j4,
                           config_arm_a1r1_joint_j5,
                           config_arm_a1r1_joint_j6],
                  'dynamatics':{'right_h2r3_fts':a1r1_dynamatics_right_h2r3_fts,
                                'left_h2r3_fts':a1r1_dynamatics_left_h2r3_fts,
                                'right_g1r1_fts':a1r1_dynamatics_right_g1r1_fts,
                                'left_g1r1_fts':a1r1_dynamatics_left_g1r1_fts,
                                'right_h2r3':a1r1_dynamatics_right_h2r3,
                                'left_h2r3':a1r1_dynamatics_left_h2r3,
                                'right_g1r1':a1r1_dynamatics_right_g1r1,
                                'left_g1r1':a1r1_dynamatics_left_g1r1,
                                'right':a1r1_dynamatics_right,
                                'left':a1r1_dynamatics_left},
                  'arm':config_arm_a1r1}
