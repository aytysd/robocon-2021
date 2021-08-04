/*
 * Control_C.cpp
 *
 *  Created on: 1 Aug 2021
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

#include "Control.hpp"
#include "main.h"
#include "General_command.hpp"
#include "Init_Move.hpp"
#include "Line.hpp"
#include "Infinity_command.hpp"
#include "Self_Pos.hpp"
#include "Jump.hpp"
#include "LED.hpp"
#include "usart.h"
#include "PWM.hpp"
#include "Rope.hpp"
#include "Time.hpp"


using namespace Infinity;


void Control::control_C( void )
{

	Line* line = new Line();
	PWM* pwm = new PWM();
	Rope* rope = new Rope();
	Time* time = new Time();



/**************************************************************************/

	line -> Line_driver( 2643, -2643, -80, 0, false );
	while( Line::judge == E_Line_status::MOVING ){};
	pwm -> rotate( 300, 0 );

	while( !( A_Rxdata[ 0 ] == ( uint8_t )E_data_type::done && B_Rxdata[ 0 ] == ( uint8_t )E_data_type::done ) ){};

/**************************************************************************/

	time -> reset_timer();

	uint8_t infinity_start_data[ DATASIZE ] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MODE_INFINITY_JUMP, 0, 0 };

	this -> send_command( E_robot_name::A, infinity_start_data );
	this -> send_command( E_robot_name::B, infinity_start_data );

	while( time -> calc_time_diff() <= ( uint32_t )E_Time::infinity ){};

	uint8_t infinity_finish_data[ DATASIZE ] = { ( uint8_t )E_data_type::stop, 0, 0, 0 };

	this -> send_command( E_robot_name::A, infinity_finish_data );
	this -> send_command( E_robot_name::B, infinity_finish_data );

/**************************************************************************/

	time -> reset_timer();

	uint8_t move_double_jump[ DATASIZE ] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MOVE_DOUBLE_JUMP_INITIAL_POS, 0, 0 };

	this -> send_command( E_robot_name::A, move_double_jump );
	this -> send_command( E_robot_name::B, move_double_jump );

	while( !( A_Rxdata[ 0 ] == ( uint8_t )E_data_type::done && B_Rxdata[ 0 ] == ( uint8_t )E_data_type::done ) ){};

/**************************************************************************/


	time -> reset_timer();

	uint8_t double_jump_start_data[ DATASIZE ] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MODE_DOUBLE_JUMP, 0, 0 };

	this -> send_command( E_robot_name::A, double_jump_start_data );
	this -> send_command( E_robot_name::B, double_jump_start_data );

	while( time -> calc_time_diff() <= ( uint32_t )E_Time::double_jump ){};

	uint8_t double_jump_finish_data[ DATASIZE ] = { ( uint8_t )E_data_type::stop, 0, 0, 0 };

	this -> send_command( E_robot_name::A, double_jump_finish_data );
	this -> send_command( E_robot_name::B, double_jump_finish_data );

/**************************************************************************/


	delete time;
	delete rope;
	delete line;
	delete pwm;
}