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
	INIT_MOVE = 0x10,
	MOVE_INFINITY_INITIAL_POS = 0x20,
	MODE_INFINITY_JUMP = 0x30,
	MODE_SELF_POS_COR = 0x40,
	MOVE_DOUBLE_JUMP_INITIAL_POS = 0x50,
	MODE_DOUBLE_JUMP = 0x60,
	FINISH = 0x70,



};


class Control
{
public:
	static uint8_t master_Rxdata[4];
	static uint8_t A_Rxdata[4];
	static uint8_t B_Rxdata[4];

	void control( E_robot_name robot );
};


#endif /* INC_CONTROL_HPP_ */
