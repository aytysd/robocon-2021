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
	Follow = 0x70,

};


class Control
{
public:

	static bool stop_flag;

	static bool A_done_flag;
	static bool B_done_flag;

	static uint8_t command[ DATASIZE ];

	void control_A( void );
	void control_B( void );
	void control_C( void );

	void send_command( E_robot_name robot, uint8_t* data );
	void send_self_pos( E_robot_name robot );
	void decode_self_pos( int16_t* x, int16_t* y, uint8_t* received_data );

	void reset_data( void );
};


#endif /* INC_CONTROL_HPP_ */
