/*
 * Control.hpp
 *
 *  Created on: 9 Jul 2021
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
#ifndef INC_CONTROL_HPP_
#define INC_CONTROL_HPP_

#include "main.h"
#include "General_command.hpp"

enum class E_Flow
{
	MOVE_INFINITY_INITIAL_POS = 0x20,
	MODE_INFINITY_JUMP = 0x30,
	MOVE_DOUBLE_JUMP_INITIAL_POS = 0x50,
	MODE_DOUBLE_JUMP = 0x60,

};


class Control
{
public:

	static bool Is_busy;

	void control_A( void );
	void control_B( void );
	void control_C( void );

	void send_command( E_robot_name robot, uint8_t* data );

};


#endif /* INC_CONTROL_HPP_ */
