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

int Jump::rope = 0;

E_move_status Jump::get_status()
{
	return this -> status;
}


void Jump::Jumping_PE_Sensor(void)
{
	Function* function = new Function();

	while(( PE_1 == false ) && ( PE_2 == false ) && ( PE_3 == false )){}
	PE_1 = false;
	PE_2 = false;
	PE_3 = false;

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

void Jump::get_Rope_Pos( uint8_t Rxdata )
{

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
