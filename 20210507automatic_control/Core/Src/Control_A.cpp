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
#include "tim.h"
#include "Debug.hpp"
#include "Stay_Jump.hpp"





void Control::control_A (void)
{

	Line* line = new Line();
	Self_Pos* self_pos = new Self_Pos();

#ifdef WITHOUT_C

	static uint8_t count;
	count++;
	switch( count )
	{
	case 1:
		Control::command[ 1 ] = ( uint8_t )E_Flow::MOVE_STAY_JUMP_POS;
		break;
	case 2:
		Control::command[ 1 ] = ( uint8_t )E_Flow::MODE_STAY_JUMP;
		break;
	case 3:
		Control::command[ 1 ] = ( uint8_t )E_Flow::MOVE_CROSS_JUMP_INITIAL_POS;
		break;
	case 4:
		Control::command[ 1 ] = ( uint8_t )E_Flow::MODE_CROSS_JUMP;
		break;
	case 5:
		Control::command[ 1 ] = ( uint8_t )E_Flow::MOVE_INFINITY_INITIAL_POS;
		break;
	case 6:
		Control::command[ 1 ] = ( uint8_t )E_Flow::MODE_INFINITY_JUMP;
		break;



	}

#endif



	switch( Control::command[1] )
	{
	case ( uint8_t )E_Flow::MOVE_STAY_JUMP_POS:
	{

		line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )SJ::A_pos::JUMP_POS_X, ( int )SJ::A_pos::JUMP_POS_Y, false, false );
		while( Line::judge == E_Line_status::MOVING ){}

		break;
	}
	case ( uint8_t )E_Flow::MODE_STAY_JUMP:
	{
		break;
	}
	case ( uint8_t )E_Flow::MOVE_CROSS_JUMP_INITIAL_POS:
	{
		line -> Line_driver( 0, 0, ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, false, false );
		while( Line::judge == E_Line_status::MOVING ){};

		break;
	}
	case ( uint8_t )E_Flow::MODE_CROSS_JUMP:
	{

#ifndef WITHOUT_C

		while( Control::stop_flag == false )
		{

#else
		for( int i = 0; i < 8; i++ )
		{

#endif

			line -> Line_driver( ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, ( int )Infinity::A_Pos::RU_X, ( int )Infinity::A_Pos::RU_Y, true, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false ){};

			line -> Line_driver( ( int )Infinity::A_Pos::RU_X, ( int )Infinity::A_Pos::RU_Y, ( int )Infinity::A_Pos::R_SPC_X, ( int )Infinity::A_Pos::R_SPC_Y, false, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

			/******************************************************************************/ // self pos correction movement


			/******************************************************************************/

			line -> Line_driver( ( int )Infinity::A_Pos::R_SPC_X, ( int )Infinity::A_Pos::R_SPC_Y, ( int )Infinity::A_Pos::RD_X, ( int )Infinity::A_Pos::RD_Y, true, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

			line -> Line_driver( ( int )Infinity::A_Pos::RD_X, ( int )Infinity::A_Pos::RD_Y, ( int )Infinity::A_Pos::LU_X, ( int )Infinity::A_Pos::LU_Y, true, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

			line -> Line_driver( ( int )Infinity::A_Pos::LU_X, ( int )Infinity::A_Pos::LU_Y, ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, false, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

			/******************************************************************************/ // self pos correction movement



			/******************************************************************************/

			line -> Line_driver( ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, true, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

		}


		Control::stop_flag = false;

		break;
	}
	case ( uint8_t )E_Flow::MOVE_INFINITY_INITIAL_POS:
	{

		HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET );


		line -> Line_driver( -2643, 2643, ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, true, false );
		while( Line::judge == E_Line_status::MOVING ){};

		line -> Line_driver( ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, false, false );
		while( Line::judge == E_Line_status::MOVING ){};

		uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::done, 0, 0, 0 };
		this -> send_command( E_robot_name::C, data );



		break;

	}
	case ( uint8_t )E_Flow::MODE_INFINITY_JUMP:
	{
		Line* line = new Line();
		LED* led = new LED();

		led -> LED_output( E_LED_status::MODE_INFINITY_JUMP );

#ifndef WITHOUT_B
		HAL_TIM_Base_Start_IT( &htim7 );
#endif

#ifndef WITHOUT_C
		while( Control::stop_flag == false )
		{
#else
		for( int i = 0; i < 8; i++ )
		{

#endif
			line -> Line_driver( ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, ( int )Infinity::A_Pos::RU_X, ( int )Infinity::A_Pos::RU_Y, true, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false ){};

			line -> Line_driver( ( int )Infinity::A_Pos::RU_X, ( int )Infinity::A_Pos::RU_Y, ( int )Infinity::A_Pos::R_SPC_X, ( int )Infinity::A_Pos::R_SPC_Y, false, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

			/******************************************************************************/ // self pos correction movement

			led -> LED_output( E_LED_status::SPC );


			led -> LED_output( E_LED_status::MODE_INFINITY_JUMP );

			/******************************************************************************/

			line -> Line_driver( ( int )Infinity::A_Pos::R_SPC_X, ( int )Infinity::A_Pos::R_SPC_Y, ( int )Infinity::A_Pos::RD_X, ( int )Infinity::A_Pos::RD_Y, true, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

			line -> Line_driver( ( int )Infinity::A_Pos::RD_X, ( int )Infinity::A_Pos::RD_Y, ( int )Infinity::A_Pos::LU_X, ( int )Infinity::A_Pos::LU_Y, true, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

			line -> Line_driver( ( int )Infinity::A_Pos::LU_X, ( int )Infinity::A_Pos::LU_Y, ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, false, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

			/******************************************************************************/ // self pos correction movement

			led -> LED_output( E_LED_status::SPC );


			led -> LED_output( E_LED_status::MODE_INFINITY_JUMP );



			/******************************************************************************/

			line -> Line_driver( ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, true, false );
			while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

		}


		Control::stop_flag = false;

		led -> LED_output( E_LED_status::Done );


	}
	default:

		break;
	}

	delete self_pos;
	delete line;



	for( int i = 0; i < DATASIZE; i++ )
		Control::command[ i ] = 0;


}

