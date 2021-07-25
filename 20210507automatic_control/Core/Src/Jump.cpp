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
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


E_move_status Jump::status = E_move_status::LANDING;

void Jump::identify()
{
	uint8_t count = 0;

	if( GPIO_PIN_RESET == HAL_GPIO_ReadPin(Under_SW_V1_2_GPIO_Port, Under_SW_V1_2_Pin )) count++;
	if( GPIO_PIN_RESET == HAL_GPIO_ReadPin(Under_SW_V3_4_GPIO_Port, Under_SW_V3_4_Pin ))count++;

	if( count >= 3 ) this -> status = E_move_status::LANDING;
	else this -> status = E_move_status::JUMPING;

}

E_move_status Jump::get_status()
{
	return this -> status;
}

void Jump::calc_fly_distance()
{
	Self_Pos* self_pos = new Self_Pos();

	uint32_t start_time = HAL_GetTick();
	while( this -> get_status() == E_move_status::JUMPING );
	uint32_t end_time = HAL_GetTick();

	int distance = this -> jump_speed * ( end_time - start_time ) / 1000;

	int add_y = ( distance / sqrt( pow( this -> x_y_prop, 2 ) + 1 ) );
	int add_x = add_y * this -> x_y_prop;

	self_pos -> add_Self_Pos( add_x, add_y );

	this -> x_y_prop = 0;
	this -> jump_speed = 0;
	delete self_pos;
}

void Jump::pre_calc()
{
	Self_Pos* self_pos = new Self_Pos();

	int prev_x = self_pos -> get_Self_Pos_X();
	int prev_y = self_pos -> get_Self_Pos_Y();

	HAL_Delay(100);

	int current_x = self_pos -> get_Self_Pos_X();
	int current_y = self_pos -> get_Self_Pos_Y();

	this -> jump_speed = sqrt( pow( ( current_x - prev_x ), 2 ) + pow( ( current_y - prev_y ), 2 ) ) / DT;

	this -> x_y_prop = ( current_x - prev_x ) / ( current_y - prev_y );

	delete self_pos;
}

void Jump::Jumping_PE_Sencor(void)
{
/*
	GPIO* gpio = new GPIO();
	if((gpio -> get_status(E_interrupt::PE_SENSOR_1) == true) || (gpio -> get_status(E_interrupt::PE_SENSOR_2) == true) || (gpio -> get_status(E_interrupt::PE_SENSOR_3) == true))
	{

	}
	delete gpio;
*/
}

void Jump::Jumping_Rope(void)
{

}
