/*
 * General.hpp
 *
 *  Created on: 14 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(General_command(e.g. robot_name)(enum_class type only))
 *
 *@Input(value)in(variable)of(functionname)
 *
 *@Output(value)to(where)
 *
 *@Attention_(begins from 0)
 *
 *@Usertouch(functionname)&_(variable_name)
 *
 */
#ifndef INC_GENERAL_COMMAND_HPP_
#define INC_GENERAL_COMMAND_HPP_



#define ROBOT E_robot_name::A
//#define ROBOT E_robot_name::B
//#define ROBOT E_robot_name::C


enum class E_robot_name
{

	A,
	B,
	C,
	NONE,
	MASTER,
};


enum class E_move_status
{
	MOVE,
	STOP,
	JUMPING,
	LANDING,
};


enum class E_Line_status
{
	MOVING,
	STOP,
	THROUGHING,
};

enum class E_data_type
{
	command = 0x10,
	done,
	stop,
	A_pos,
	B_pos,
	C_pos,
};

#define NC 0xFE





#endif /* INC_GENERAL_COMMAND_HPP_ */
