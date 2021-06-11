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
#include "GPIO.hpp"
#include "main.h"

E_move_status Jump::status = E_move_status::LANDING;

void Jump::identify()
{
	uint8_t count = 0;

	if( GPIO_PIN_SET == HAL_GPIO_ReadPin(Under_SW_V1_2_GPIO_Port, Under_SW_V1_2_Pin ))
	{
		count++;
	}
	if( GPIO_PIN_SET == HAL_GPIO_ReadPin(Under_SW_V2_3_GPIO_Port, Under_SW_V2_3_Pin ))
	{
		count++;
	}
	if( GPIO_PIN_SET == HAL_GPIO_ReadPin(Under_SW_V3_4_GPIO_Port, Under_SW_V3_4_Pin ))
	{
		count++;
	}
	if( GPIO_PIN_SET == HAL_GPIO_ReadPin(Under_SW_V1_4_GPIO_Port, Under_SW_V1_4_Pin ))
	{
		count++;
	}

	if( count >= 3 )
	{
		this -> status = E_move_status::LANDING;
	}
	else
	{
		this -> status = E_move_status::JUMPING;
	}

}

E_move_status Jump::get_status()
{
	return this -> status;
}

