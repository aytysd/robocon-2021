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
 *
 *@Attention_(description)
 *
 *@Usertouch(functionname)&_(variable_name)
 *
 */
#ifndef INC_FUNCTION_HPP_
#define INC_FUNCTION_HPP_

#include "main.h"

class Function{
public:
	void drive_motor(uint8_t motor_number, uint8_t direction, uint8_t PWM);
	void drive_solenoid_valve(int port_number, int ON_OFF);
};



#endif /* INC_FUNCTION_HPP_ */
