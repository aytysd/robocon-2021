/*
 * Function.hpp
 *
 *  Created on: 7 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(activate motor, solenoid valve, and LED)
 *
 *@Input(motor_number)in(uint8_t motor_number)of(void drive_motor)
 *@Input(direction ( 0:Free, 1:CW, 2:CCW, 3:Brake )in(uint8_t direction)of(void drive_motor)
 *@Input(PWM)in(uint8_t PWM)of(void drive_motor)
 *@Input(speed you expect)in(uint16_t speed)of(void drive_motor)
 *@Input(PID_Enabled ( enable:true, disable:false, )in(bool PID_Enabled)of(void drive_motor)
 *
 *@Output(motor_number, direction, PWM)to(MDC)
 *@Output(color(1:Red, 2:Green, 3:Blue),brightness(0~20))to(LED)
 *
 *@Attention_(description)
 *
 *@Usertouch(void drive_motor)&_(variable_name)
 *
 */
#ifndef INC_FUNCTION_HPP_
#define INC_FUNCTION_HPP_

#include "main.h"

class Function{
public:
	void drive_motor(uint8_t motor_number, uint8_t direction, uint8_t PWM, uint16_t speed, bool PID_Enabled);
	void drive_solenoid_valve(int port_number, int ON_OFF);
	void drive_LED(int color, int brightness);
};



#endif /* INC_FUNCTION_HPP_ */
