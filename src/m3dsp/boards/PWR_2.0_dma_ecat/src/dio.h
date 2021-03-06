/* 
M3 -- Meka Robotics Real-Time Control System
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


#ifndef __DIO_H__
#define __DIO_H__ 

#ifdef USE_DIO
#include "setup.h"

#define SetHeartbeatLED	LATAbits.LATA4=1
#define ClrHeartbeatLED	LATAbits.LATA4=0
#define PinHeartbeatLED PORTAbits.RA4
void ToggleHeartbeatLED(void);

#define SetTimestampLatch LATCbits.LATC3 = 1
#define ClrTimestampLatch LATCbits.LATC3 = 0

#if defined PWR_0_2 || defined PWR_0_3 || defined PWR_0_4 || defined PWR_0_5
#define SetEnableMotor	LATBbits.LATB12=1
#define ClrEnableMotor	LATBbits.LATB12=0
#define PinModeRemote	PORTBbits.RB5
#define PinMotorEnabled PORTBbits.RB6
#if defined PWR_0_3 || defined PWR_0_4 || defined PWR_0_5
#define SetPwrStatusLED LATBbits.LATB13=1
#define ClrPwrStatusLED LATBbits.LATB13=0
#define PinPwrStatusLED PORTBbits.RB13
void TogglePwrStatusLED(void);
int GetMotorEnabledFiltered(); //Power supply issue, causes spurious disable
#endif

#if defined PWR_0_5 && defined USE_BUZZER
#define	BUZZER					LATBbits.LATB11		//RB11	OUTPUT	PIN9	BUZZER
#define BUZZER_SET				BUZZER=1; 
#define BUZZER_CLR				BUZZER=0; 
#endif

#endif

void setup_dio(void);

#endif
#endif
