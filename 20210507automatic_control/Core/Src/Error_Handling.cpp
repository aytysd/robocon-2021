/*
 * Error_Handler.cpp
 *
 *  Created on: Jun 5, 2021
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

#include <Error_Handling.hpp>
#include "main.h"
#include "Function.hpp"
#include "Communication.hpp"
#include "LED.hpp"

void Error_Handling::TIM5_error_handling()
{
	static bool flag = false;
	static uint32_t base_time = 0;

	if( flag == false )
	{
		base_time = HAL_GetTick();
	}



	 if( TIM5 -> CNT == 0 )
	 {

		 if( ( HAL_GetTick() - base_time ) >= 5000 )
		 {
			 Communication* communication = new Communication();
			 this -> warning_line = __LINE__;
			 this -> warning_func = const_cast<char*>(__func__);
			 this -> set_flag(E_Errors::W_X_Encoder_Disconnection);
			 communication -> send_data( E_data_type::WARNING_DATA );
			 delete communication;

			 LED* led = new LED();
			 led -> LED_output(E_LED_status::Warning);
			 delete led;
		 }

		 flag = true;
	 }
	 else
	 {
		 LED* led = new LED();
		 led -> LED_output(LED::old_LED_status);
		 delete led;

		 flag = false;
	 }

}

void Error_Handling::TIM2_error_handling()
{
	static bool flag = false;
	static uint32_t base_time = 0;

	if( flag == false )
	{
		base_time = HAL_GetTick();
	}



	 if( TIM2 -> CNT == 0 )
	 {

		 if( ( HAL_GetTick() - base_time ) >= 5000 )
		 {
			 Communication* communication = new Communication();

			 this -> warning_line = __LINE__;
			 this -> warning_func = const_cast<char*>(__func__);
			 this -> set_flag(E_Errors::W_Y_Encoder_Disconnection);

			 communication -> send_data( E_data_type::WARNING_DATA );
			 delete communication;

			 LED* led = new LED();
			 led -> LED_output(E_LED_status::Warning);
			 delete led;


		 }

		 flag = true;
	 }
	 else
	 {
		 LED* led = new LED();
		 led -> LED_output(LED::old_LED_status);
		 delete led;

		 flag = false;
	 }

}

void Error_Handling::gyro_error_handling(uint16_t direction)
{
	static bool flag = false;
	static uint32_t base_time = 0;

	if( flag == false )
	{
		base_time = HAL_GetTick();
	}



	 if( direction == 0 || direction == 41 || direction > 360 )
	 {

		 if( ( HAL_GetTick() - base_time ) >= 5000 )
		 {
			 Communication* communication = new Communication();

			 this -> warning_line = __LINE__;
			 this -> warning_func = const_cast<char*>(__func__);
			 this -> set_flag(E_Errors::W_gyro_Disconnection);

			 communication -> send_data( E_data_type::WARNING_DATA );
			 delete communication;

			 LED* led = new LED();
			 led -> LED_output(E_LED_status::Warning);
			 delete led;


		 }

		 flag = true;
	 }
	 else
	 {
		 LED* led = new LED();
		 led -> LED_output(LED::old_LED_status);
		 delete led;

		 flag = false;
	 }

}


void Error_Handling::Emergency_stop()
{
	Function* function = new Function();
	for(int i = 0; i<8; i++){

		function -> drive_motor(i, 3, 0, false, false);
	}
	delete function;

}

void Error_Handling::set_flag(E_Errors errors)
{
	for( int i = 0; i<static_cast<int>(E_Errors::Count); i++)
	{
		if( static_cast<int>(errors) == i )
		{
			this -> flag[i] = true;
		}
	}

}


const char* Error_Handling::error_func = 0;
uint32_t Error_Handling::error_line = 0;

char* Error_Handling::current_func = 0;
uint32_t Error_Handling::current_line = 0;

char* Error_Handling::warning_func = 0;
uint32_t Error_Handling::warning_line = 0;

bool Error_Handling::flag[ static_cast<int>(E_Errors::Count) + 1 ] = { false, false, false, false, false, false };
