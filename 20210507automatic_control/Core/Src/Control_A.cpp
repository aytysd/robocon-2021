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
#include "PWM.hpp"
#include "usart.h"
#include "tim.h"
#include "Debug.hpp"
#include "Stay_Jump.hpp"
#include "Control_A.hpp"
#include "Jump.hpp"
#include "math.h"


bool Control_A::start_flag = false;

void Control_A::control_A (void)
{

#ifdef WITHOUT_C

	static uint8_t count;
	count++;
	switch( count )
	{
	case 1:
		Control::command[ 1 ] = ( uint8_t )E_Flow::MODE_STAY_JUMP;
		HAL_Delay( 3000 );
		break;
	case 2:
		Control::command[ 1 ] = ( uint8_t )E_Flow::MODE_CROSS_JUMP;
		HAL_Delay( 3000 );
		break;
	case 3:
		Control::command[ 1 ] = ( uint8_t )E_Flow::MODE_INFINITY_JUMP;
		HAL_Delay( 3000 );
		break;

	}

#endif



	switch( Control::command[1] )
	{
	case ( uint8_t )E_Flow::MODE_STAY_JUMP:
		this -> stay_jump();
		break;
	case ( uint8_t )E_Flow::MODE_CROSS_JUMP:
		this -> cross_jump();
		break;
	case ( uint8_t )E_Flow::MODE_INFINITY_JUMP:
		this -> infinity_jump();
		break;
	}

	for( int i = 0; i < DATASIZE; i++ )
		Control::command[ i ] = 0;


}


void Control_A::stay_jump( void )
{

	Control* control = new Control();
	Line* line = new Line();
	Jump* jump = new Jump();
	Self_Pos* self_pos = new Self_Pos();

	line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )SJ::A_pos::JUMP_POS_X, ( int )SJ::A_pos::JUMP_POS_Y, false, false );
	while( Line::judge == E_Line_status::MOVING ){}

	uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::ready };
	control -> send_command( E_robot_name::C, data );

#ifndef WITHOUT_C
	while( Control_A::start_flag == false ){};
#endif

	Control::stop_flag = false;
	Control_A::start_flag = false;

	delete line;
	delete self_pos;
	delete control;
	delete jump;


}

void Control_A::cross_jump( void )
{
	Control* control = new Control();
	Line* line = new Line();
	Jump* jump = new Jump();
	Self_Pos* self_pos = new Self_Pos();
	PWM* pwm = new PWM();

	line -> Line_driver( 0, 0, ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, false, false );
	while( Line::judge == E_Line_status::MOVING ){};

	uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::ready };
	control -> send_command( E_robot_name::C, data );



#ifndef WITHOUT_C

	while( Control_A::start_flag == false ){};

	HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET );

	while( Control::stop_flag == false )
	{

#else
	for( int i = 0; i < 4; i++ )
	{

#endif

		line -> Line_driver( ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, ( int )Infinity::A_Pos::RU_X, ( int )Infinity::A_Pos::RU_Y, true, true );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false ){};

		/******************************************************************************/

		while( jump -> Is_centre() == false ){};
		jump -> jump();


		/******************************************************************************/

		line -> Line_driver( ( int )Infinity::A_Pos::RU_X, ( int )Infinity::A_Pos::RU_Y, ( int )Infinity::A_Pos::R_SPC_X, ( int )Infinity::A_Pos::R_SPC_Y, false, false );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

		/******************************************************************************/ // self pos correction movement


		/******************************************************************************/

		line -> Line_driver( ( int )Infinity::A_Pos::R_SPC_X, ( int )Infinity::A_Pos::R_SPC_Y, ( int )Infinity::A_Pos::RD_X, ( int )Infinity::A_Pos::RD_Y, true, false );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

		line -> Line_driver( ( int )Infinity::A_Pos::RD_X, ( int )Infinity::A_Pos::RD_Y, ( int )Infinity::A_Pos::LU_X, ( int )Infinity::A_Pos::LU_Y, true, true );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

		/******************************************************************************/


		while( jump -> Is_centre() == false ){};
		jump -> jump();




		/******************************************************************************/

		line -> Line_driver( ( int )Infinity::A_Pos::LU_X, ( int )Infinity::A_Pos::LU_Y, ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, false, false );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

		/******************************************************************************/ // self pos correction movement



		/******************************************************************************/

		line -> Line_driver( ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, true, false );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

	}

	pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );

	Control_A::start_flag = false;
	Control::stop_flag = false;


	delete line;
	delete pwm;
	delete jump;
	delete self_pos;
	delete control;
}

void Control_A::infinity_jump( void )
{
	Control* control = new Control();
	Line* line = new Line();
	Jump* jump = new Jump();
	Self_Pos* self_pos = new Self_Pos();
	PWM* pwm = new PWM();

	HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET );


	line -> Line_driver( -2643, 2643, ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, true, false );
	while( Line::judge == E_Line_status::MOVING ){};

	line -> Line_driver( ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, false, false );
	while( Line::judge == E_Line_status::MOVING ){};

	uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::ready };
	control -> send_command( E_robot_name::C, data );




#ifndef WITHOUT_C

	while( Control_A::start_flag == false ){};

	while( Control::stop_flag == false )
	{
#else
	for( int i = 0; i < 4; i++ )
	{

#endif
		line -> Line_driver( ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, ( int )Infinity::A_Pos::RU_X, ( int )Infinity::A_Pos::RU_Y, true, true );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false ){};

		/******************************************************************************/


		while( jump -> Is_centre() == false ){};
		jump -> jump();



		/******************************************************************************/

		line -> Line_driver( ( int )Infinity::A_Pos::RU_X, ( int )Infinity::A_Pos::RU_Y, ( int )Infinity::A_Pos::R_SPC_X, ( int )Infinity::A_Pos::R_SPC_Y, false, false );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

		/******************************************************************************/ // self pos correction movement


		/******************************************************************************/

		line -> Line_driver( ( int )Infinity::A_Pos::R_SPC_X, ( int )Infinity::A_Pos::R_SPC_Y, ( int )Infinity::A_Pos::RD_X, ( int )Infinity::A_Pos::RD_Y, true, false );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

		line -> Line_driver( ( int )Infinity::A_Pos::RD_X, ( int )Infinity::A_Pos::RD_Y, ( int )Infinity::A_Pos::LU_X, ( int )Infinity::A_Pos::LU_Y, true, true );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};


		/******************************************************************************/


		while( jump -> Is_centre() == false ){};
		jump -> jump();



		/******************************************************************************/


		line -> Line_driver( ( int )Infinity::A_Pos::LU_X, ( int )Infinity::A_Pos::LU_Y, ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, false, false );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

		/******************************************************************************/ // self pos correction movement


		/******************************************************************************/

		line -> Line_driver( ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, true, false );
		while( Line::judge == E_Line_status::MOVING && Control::stop_flag == false  ){};

	}

	pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );


	Control::stop_flag = false;
	Control_A::start_flag = false;


	delete pwm;
	delete line;
	delete self_pos;
	delete jump;
	delete control;


}

