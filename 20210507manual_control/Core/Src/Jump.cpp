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
#include "math.h"
#include "function.hpp"
#include "Controller.hpp"
#include "usart.h"

E_Jump_status Jump::Jump_status = E_Jump_status::Jump_disable;


void Jump::Jump_driver( E_Jump_status status)
{
	this -> Jump_status = status;
}

E_Jump_status Jump::get_Jump_status( void )
{
	return this -> Jump_status;
}

void Jump::jump( void )
{
	this -> Jump_status = E_Jump_status ::Jump_enable;
	HAL_GPIO_WritePin( GPIOC, GPIO_PIN_2, GPIO_PIN_SET );

	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_RESET );
	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_SET );// || ( ( HAL_GetTick() - start_time ) < 3000 ) );
	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_RESET );

	HAL_GPIO_WritePin( GPIOC, GPIO_PIN_2, GPIO_PIN_RESET );
  
	this -> Jump_status = E_Jump_status::Jump_disable;
  
}




