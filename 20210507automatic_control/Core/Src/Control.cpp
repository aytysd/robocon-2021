/*
 * Control.cpp
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
 *@Attention_(uint8_t Control::master_Rxdata[0] = Flow_command
 *											[1] =
 *@Usertouch(functionname)&_(variable_name)
 *
 */

#include "Control.hpp"
#include "main.h"
#include "General_command.hpp"
#include "Init_Move.hpp"

uint8_t Control::master_Rxdata[4] = { 0, 0, 0, 0 };
uint8_t Control::A_Rxdata[4] = { 0, 0, 0, 0 };
uint8_t Control::B_Rxdata[4] = { 0, 0, 0, 0 };

void Control::control()
{
/*
	if( Control::master_Rxdata[0] == (uint8_t)E_Flow::INIT_MOVE )
	{
		Init_Move* init_move = new Init_Move();
		init_move -> init_move( E_robot_name::A );
		delete init_move;
	}
*/
}