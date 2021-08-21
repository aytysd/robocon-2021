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

bool Control::A_done_flag = false;
bool Control::B_done_flag = false;

void Control::control_C( void )
{

	Line* line = new Line();
	PWM* pwm = new PWM();
	Rope* rope = new Rope();
	Time* time = new Time();
	LED* led = new LED();


/**************************************************************************/

	led -> LED_output( E_LED_status::MOVE_INFINITY_INITIAL_POS );
	line -> Line_driver( 2643, -2643, -80, 0, false );
	while( Line::judge == E_Line_status::MOVING ){};
	pwm -> rotate( 300, 0 );

	Line::Enable_line = false;

#ifndef WITHOUT_B
	while( !( Control::A_done_flag == true && Control::B_done_flag == true ) ){};

	Control::A_done_flag = false;
	Control::B_done_flag = false;

#else
	while( !( Control::A_done_flag == true ) ){};

	Control::A_done_flag = false;

#endif

	led -> LED_output( E_LED_status::Done );
	HAL_Delay( 3000 );

/**************************************************************************/

	time -> reset_timer();

	led -> LED_output( E_LED_status::MODE_INFINITY_JUMP );

	uint8_t infinity_start_data[ DATASIZE ] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MODE_INFINITY_JUMP, 0, 0 };

	this -> send_command( E_robot_name::A, infinity_start_data );
#ifndef WITHOUT_B
	this -> send_command( E_robot_name::B, infinity_start_data );
#endif

	while( time -> calc_time_diff() <= ( uint32_t )E_Time::infinity ){};

	uint8_t infinity_finish_data[ DATASIZE ] = { ( uint8_t )E_data_type::stop, 0, 0, 0 };

	this -> send_command( E_robot_name::A, infinity_finish_data );
#ifndef WITHOUT_B
	this -> send_command( E_robot_name::B, infinity_finish_data );
#endif

	led -> LED_output( E_LED_status::MOVE_DOUBLE_JUMP_INITIAL_POS );

/**************************************************************************/

	time -> reset_timer();

	uint8_t move_double_jump[ DATASIZE ] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MOVE_DOUBLE_JUMP_INITIAL_POS, 0, 0 };

	this -> send_command( E_robot_name::A, move_double_jump );
#ifndef WITHOUT_B
	this -> send_command( E_robot_name::B, move_double_jump );
#endif


#ifndef WITHOUT_B
	while( !( Control::A_done_flag == true && Control::B_done_flag == true ) ){};

	Control::A_done_flag = false;
	Control::B_done_flag = false;


#else
	while( !( Control::A_done_flag == true ) ){};
	Control::A_done_flag = false;

#endif

	led -> LED_output( E_LED_status::Done );
	HAL_Delay( 3000 );

/**************************************************************************/


	time -> reset_timer();

	led -> LED_output( E_LED_status::MODE_DOUBLE_JUMP );

	uint8_t double_jump_start_data[ DATASIZE ] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MODE_DOUBLE_JUMP, 0, 0 };

	this -> send_command( E_robot_name::A, double_jump_start_data );
#ifndef WITHOUT_B
	this -> send_command( E_robot_name::B, double_jump_start_data );
#endif

	while( time -> calc_time_diff() <= ( uint32_t )E_Time::double_jump ){};

	uint8_t double_jump_finish_data[ DATASIZE ] = { ( uint8_t )E_data_type::stop, 0, 0, 0 };

	this -> send_command( E_robot_name::A, double_jump_finish_data );
#ifndef WITHOUT_B
	this -> send_command( E_robot_name::B, double_jump_finish_data );
#endif

	led -> LED_output( E_LED_status::Done );

/**************************************************************************/

	delete led;
	delete time;
	delete rope;
	delete line;
	delete pwm;
}
