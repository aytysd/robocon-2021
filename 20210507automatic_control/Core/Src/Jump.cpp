/*
 * Jump.cpp
 *
 *  Created on: 9 May 2021
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

#include "Jump.hpp"
#include "General_command.hpp"
#include "hGPIO.hpp"
#include "main.h"
#include "Self_Pos.hpp"
#include "math.h"
#include "function.hpp"
#include "Self_Pos.hpp"

E_move_status Jump::status = E_move_status::LANDING;

bool Jump::PE_1 = false;
bool Jump::PE_2 = false;
bool Jump::PE_3 = false;
bool Jump::PE_4 = false;
bool Jump::PE_5 = false;

int Jump::rope = 0;

E_move_status Jump::get_status()
{
	return this -> status;
}


void Jump::Jumping_PE_Sensor(void)
{
	Function* function = new Function();

	while(( this -> get_PE_status( PE_Jump ) == false )){}

	this -> jump();
	delete function;
}

void Jump::Jumping_Rope(void)
{

}

void Jump::jump( void )
{
	HAL_GPIO_WritePin( GPIOC, GPIO_PIN_2, GPIO_PIN_SET );

	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_RESET );
	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_SET );
	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_RESET );
//	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_SET );
//	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_RESET );
//	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_SET );
//	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_RESET );

	HAL_GPIO_WritePin( GPIOC, GPIO_PIN_2, GPIO_PIN_RESET );


}


bool Jump::Is_centre( void )
{

	Self_Pos* self_pos = new Self_Pos();

	double distance = sqrt( ( self_pos -> get_Self_Pos_X() ^ 2 ) + ( self_pos -> get_Self_Pos_Y() ^ 2 ) );

	if( distance < 300 )
		return true;
	else
		return false;

}


void Jump::PE_Sensor( int PE_num )
{
	switch( PE_num )
	{
	case 1:
		this -> PE_1 = true;
		break;
	case 2:
		this -> PE_2 = true;
		break;
	case 3:
		this -> PE_3 = true;
		break;
	case 4:
		this -> PE_4 = true;
		break;
	case 5:
		this -> PE_5 = true;
		break;
	default:
		break;
	}
}

bool Jump::get_PE_status( int func )
{
	switch( func )
	{
	case PE_Jump:
		if(( this -> PE_1 == true ) || ( this -> PE_2 == true ) || ( this -> PE_3 == true ))
		{
			this -> PE_init();
			return true;
		}
		else
		{
			return false;
		}
		break;
	case PE_Self_Pos:
		if(( this -> PE_4 == true ) || ( this -> PE_5 == true ))
		{
			this -> PE_init();
			return true;
		}
		else
		{
			return false;
		}
		break;
	default:
		break;
	}
}

void Jump::PE_init()
{
	this -> PE_1 = false;
	this -> PE_2 = false;
	this -> PE_3 = false;
	this -> PE_4 = false;
	this -> PE_5 = false;
}
