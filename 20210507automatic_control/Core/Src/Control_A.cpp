/*
 * Control_A.cpp
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



int Infinity::A_pos_X[ 6 ] = { -1200, 1200, 2400, 1200, -1200, -2400 };
int Infinity::A_pos_Y[ 6 ] = { -1200, 1200, 0, 1200, 1200, 0 };


bool Control::A_Is_busy = false;
bool Control::A_stop_flag = false;

void Control::control_A (void)
{


	Control::A_Is_busy = true;

	switch( Control::C_command[1] )
	{
	case ( uint8_t )E_Flow::MOVE_INFINITY_INITIAL_POS:
	{
		Line* line = new Line();
		Self_Pos* self_pos = new Self_Pos();
		LED* led = new LED();

		led -> LED_output( E_LED_status::MOVE_INFINITY_INITIAL_POS );

		line -> Line_driver( -2643, 2643, ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, true );
		while( Line::judge == E_Line_status::MOVING ){};

		line -> Line_driver( ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, false );
		while( Line::judge == E_Line_status::MOVING ){};

		uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::done, 0, 0, 0 };
		this -> send_command( E_robot_name::C, data );

		led -> LED_output( E_LED_status::Done );

		delete led;
		delete line;
		delete self_pos;

		break;

	}
	case ( uint8_t )E_Flow::MODE_INFINITY_JUMP:
	{
		Line* line = new Line();
		LED* led = new LED();



		while( Control::A_stop_flag == false )
		{


			led -> LED_output( E_LED_status::MODE_INFINITY_JUMP );

			line -> Line_driver( ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, ( int )Infinity::A_Pos::RU_X, ( int )Infinity::A_Pos::RU_Y, true );
			while( Line::judge == E_Line_status::MOVING && Control::A_stop_flag == false ){};

			line -> Line_driver( ( int )Infinity::A_Pos::RU_X, ( int )Infinity::A_Pos::RU_Y, ( int )Infinity::A_Pos::R_SPC_X, ( int )Infinity::A_Pos::R_SPC_Y, false );
			while( Line::judge == E_Line_status::MOVING && Control::A_stop_flag == false  ){};

			/******************************************************************************/ // self pos correction movement

			led -> LED_output( E_LED_status::SPC );


			led -> LED_output( E_LED_status::MODE_INFINITY_JUMP );

			/******************************************************************************/

			line -> Line_driver( ( int )Infinity::A_Pos::R_SPC_X, ( int )Infinity::A_Pos::R_SPC_Y, ( int )Infinity::A_Pos::RD_X, ( int )Infinity::A_Pos::RD_Y, true );
			while( Line::judge == E_Line_status::MOVING && Control::A_stop_flag == false  ){};

			line -> Line_driver( ( int )Infinity::A_Pos::RD_X, ( int )Infinity::A_Pos::RD_Y, ( int )Infinity::A_Pos::LU_X, ( int )Infinity::A_Pos::LU_Y, true );
			while( Line::judge == E_Line_status::MOVING && Control::A_stop_flag == false  ){};

			line -> Line_driver( ( int )Infinity::A_Pos::LU_X, ( int )Infinity::A_Pos::LU_Y, ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, false );
			while( Line::judge == E_Line_status::MOVING && Control::A_stop_flag == false  ){};

			/******************************************************************************/ // self pos correction movement

			led -> LED_output( E_LED_status::SPC );


			led -> LED_output( E_LED_status::MODE_INFINITY_JUMP );



			/******************************************************************************/

			line -> Line_driver( ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, true );
			while( Line::judge == E_Line_status::MOVING && Control::A_stop_flag == false  ){};

		}


		Control::A_stop_flag = false;

		led -> LED_output( E_LED_status::Done );

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

		while( Control::A_stop_flag == false ){};

		led -> LED_output( E_LED_status::Done );


		delete led;

		break;
	}
	default:

		break;
	}


	Control::A_Is_busy = false;

	for( int i = 0; i < DATASIZE; i++ )
		Control::C_command[ i ] = 0;


}
