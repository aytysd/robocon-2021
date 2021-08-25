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

E_move_status Jump::status = E_move_status::LANDING;

bool Jump::PE_1 = false;
bool Jump::PE_2 = false;
bool Jump::PE_3 = false;


E_move_status Jump::get_status()
{
	return this -> status;
}


void Jump::Jumping_PE_Sensor(void)
{
	Function* function = new Function();
	while( (PE_1 == true) || (PE_2 == true) || (PE_3 == true))
	{
	//	function -> drive_motor(5, CW, this -> speed_jump - 500, false, true);;
	}
	delete function;
}

void Jump::Jumping_Rope(void)
{

}

void Jump::jump( void )
{
	HAL_GPIO_WritePin( GPIOC, GPIO_PIN_2, GPIO_PIN_SET );

	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_SET );

	HAL_GPIO_WritePin( GPIOC, GPIO_PIN_2, GPIO_PIN_RESET );


}

