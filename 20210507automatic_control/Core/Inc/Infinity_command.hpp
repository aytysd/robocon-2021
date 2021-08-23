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

extern int A_pos_X[ 6 ];
extern int A_pos_Y[ 6 ];

enum class A_Pos
{

	LD_X = -1200,
	LD_Y = -2000,

	JUMP_X = 0,
	JUMP_Y = 0,

	RU_X = 1200,
	RU_Y = 2000,

	R_SPC_X = 2400,
	R_SPC_Y = 0,

	RD_X = 1200,
	RD_Y = -2000,

	LU_X = -1200,
	LU_Y = 2000,

	L_SPC_X = -2400,
	L_SPC_Y = 0,

};

enum class B_Pos
{

};

}





#endif /* INC_INFINITY_COMMAND_HPP_ */
