/*
 * Infinity_command.hpp
 *
 *  Created on: 14 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(commands of initfinity loop)
 *
 *@Input(value)in(variable)of(functionname)
 *
 *@Output(value)to(where)
 *
 *@Attention_(begins from 75)
 *
 *@Usertouch(functionname)&_(variable_name)
 *
 */
#ifndef INC_INFINITY_COMMAND_HPP_
#define INC_INFINITY_COMMAND_HPP_

namespace Infinity
{

int A_pos_X[ 6 ] = { -1200, 1200, 2400, 1200, -1200, -2400 };
int A_pos_Y[ 6 ] = { -1200, 1200, 0, 1200, 1200, 0 };

enum class A_Pos
{

	LD_X = -1200,
	LD_Y = -1200,

	JUMP_X = 0,
	JUMP_Y = 0,

	RU_X = 1200,
	RU_Y = 1200,

	R_SPC_X = 2400,
	R_SPC_Y = 0,

	RD_X = 1200,
	RD_Y = -1200,

	LU_X = -1200,
	LU_Y = 1200,

	L_SPC_X = -2400,
	L_SPC_Y = 0,

};

enum class B_Pos
{

};

}





#endif /* INC_INFINITY_COMMAND_HPP_ */
