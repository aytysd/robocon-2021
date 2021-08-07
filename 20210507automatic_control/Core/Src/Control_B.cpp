/*
 * Control_B.cpp
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
#include "Follow.hpp"


using namespace Infinity;

void Control::control_B( void )
{


	switch( Control::command[ 1 ] )
	{
	case ( uint8_t )E_Flow::MOVE_INFINITY_INITIAL_POS:
	{
		Line* line = new Line();
		LED* led = new LED();

		led -> LED_output( E_LED_status::MOVE_INFINITY_INITIAL_POS );

		line -> Line_driver( -2643, -2643, -1700, -1700, false );
		while( Line::judge == E_Line_status::MOVING ){};

		uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::done, 0, 0, 0 };
		this -> send_command( E_robot_name::C, data );

		led -> LED_output( E_LED_status::Done );

		delete led;
		delete line;

		break;


	}
	case ( uint8_t )E_Flow::MODE_INFINITY_JUMP:
	{
		Line* line = new Line();
		LED* led = new LED();



		while( Control::stop_flag == false )
		{

			led -> LED_output( E_LED_status::MODE_INFINITY_JUMP );

			Follow* follow = new Follow();
			follow -> follow();
			delete follow;




			/******************************************************************************/ // self pos correction movement

			led -> LED_output( E_LED_status::SPC );


			led -> LED_output( E_LED_status::MODE_INFINITY_JUMP );

			/******************************************************************************/


			/******************************************************************************/ // self pos correction movement

			led -> LED_output( E_LED_status::SPC );


			led -> LED_output( E_LED_status::MODE_INFINITY_JUMP );



			/******************************************************************************/


		}



		led -> LED_output( E_LED_status::Done );
		Control::stop_flag = false;

		delete led;
		delete line;
		break;

	}
	case ( uint8_t )E_Flow::MOVE_DOUBLE_JUMP_INITIAL_POS:
	{
		Line* line = new Line();
		Self_Pos* self_pos = new Self_Pos();
		LED* led = new LED();

		led -> LED_output( E_LED_status::MOVE_DOUBLE_JUMP_INITIAL_POS );


		uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::done, 0, 0, 0 };
		this -> send_command( E_robot_name::C, data );

		led -> LED_output( E_LED_status::Done );

		delete led;
		delete line;
		delete self_pos;

		break;
	}
	case ( uint8_t )E_Flow::MODE_DOUBLE_JUMP:
	{
		LED* led = new LED();

		led -> LED_output( E_LED_status::MODE_DOUBLE_JUMP );

		while( Control::stop_flag == false ){};

		led -> LED_output( E_LED_status::Done );


		delete led;

		break;
	}
	default:

		break;
	}



	for( int i = 0; i < DATASIZE; i++ )
		Control::command[ i ] = 0;

}

