/*
 * Control.cpp
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
 *@Attention_(uint8_t Control::master_Rxdata = Flow_command
 *											[1] =
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


uint8_t Control::C_command[ DATASIZE ] = { 0, 0, 0, 0 };

void Control::send_command( E_robot_name robot, uint8_t* data )
{

	switch( robot )
	{
	case E_robot_name::A:
		HAL_UART_Transmit( &huart1, ( uint8_t* )data, sizeof( data ), 100 );
		break;
	case E_robot_name::B:
		HAL_UART_Transmit( &huart4, ( uint8_t* )data, sizeof( data ), 100 );
		break;
	case E_robot_name::C:
		HAL_UART_Transmit( &huart3, ( uint8_t* )data, sizeof( data ), 100 );
		break;
	}

}

void Control::send_self_pos( E_robot_name robot )
{
	Self_Pos* self_pos = new Self_Pos();

	int16_t x = self_pos -> get_Self_Pos_X();
	int16_t y = self_pos -> get_Self_Pos_Y();

	uint8_t self_pos_x_p = ( 0b1111111100000000 & x ) >> 8;
	uint8_t self_pos_x_q = ( 0b0000000011111111 & x );

	uint8_t self_pos_y_p = ( 0b1111111100000000 & y ) >> 8;
	uint8_t self_pos_y_q = ( 0b0000000011111111 & y );

	uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::A_pos, self_pos_x_p, self_pos_x_q, self_pos_y_p, self_pos_y_q, 0, 0, 0 };
	this -> send_command( robot, data );


	delete self_pos;


}

void Control::decode_self_pos( int16_t* x, int16_t* y, uint8_t* received_data )
{

	*x = 0;
	*y = 0;

	*x = received_data[ 1 ] << 8;
	*x |= received_data[ 2 ];

	*y = received_data[ 3 ] << 8;
	*y = received_data[ 4 ];

}

