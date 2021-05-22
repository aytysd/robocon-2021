/*
 * Init_Move.cpp
 *
 *  Created on: 14 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(description_about_thisclass)
 *
 *@Input(value)in(variable)of(functionname)
 *
 *@Output(value)to(where)
 *
 *@Attention_(description)
 *
 *@Usertouch(functionname)&_(variable_name)
 *
 */

#include "Init_Move.hpp"
#include "General_command.hpp"
#include "PWM.hpp"

void Init_Move::init_move(E_robot_name robot){

	PWM* pwm = new PWM();

	switch(robot){
	case E_robot_name::A:
		pwm -> V_output(100, 90, 0, 0, E_move_status::MOVE);
		break;
	case E_robot_name::B:
		pwm -> V_output(100, 180, 0, 90, E_move_status::MOVE);
		break;
	case E_robot_name::C:
		pwm -> V_output(100, 270, 0, 180, E_move_status::MOVE);
		break;
	}

}

