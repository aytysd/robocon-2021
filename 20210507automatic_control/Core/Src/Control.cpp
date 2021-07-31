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


bool Control::Is_busy = false;

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

