/*
 * Function.hpp
 *
 *  Created on: 7 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(activate motor and solenoid valve)
 *
 *@Input(value)in(variable)of(functionname)
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
	void drive_motor(uint8_t motor_number, uint8_t direction, uint8_t PWM, uint16_t speed);
	void drive_solenoid_valve(int port_number, int ON_OFF);
	void drive_LED(int color, int brightness);
};



#endif /* INC_FUNCTION_HPP_ */
