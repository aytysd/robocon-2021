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


#define MANU





enum class E_robot_name
{

	A,
	B,
	C,
};


enum class E_move_status
{
	MOVE,
	STOP,
	JUMPING,
	LANDING,
};




enum class E_Jump_status
{
	Jump_enable,
	Jump_disable,
	Jump_Jumping,

};





#endif /* INC_GENERAL_COMMAND_HPP_ */
