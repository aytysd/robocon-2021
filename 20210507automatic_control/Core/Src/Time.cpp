/*
 * Time.cpp
 *
 *  Created on: 13 Jul 2021
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

#include "Time.hpp"
#include "stdio.h"
#include "main.h"



void Time::time_calc(void)
{
	static int i;
	static uint32_t start_time;
	static uint32_t end_time;

	i++;


	switch( i % 2 )
	{
	case 1:
		start_time = HAL_GetTick();
		break;
	case 0:
	{
		end_time = HAL_GetTick();
		uint32_t diff = end_time - start_time;

		char output[10];
		sprintf( output, "%d\r\n", diff );
		HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );

		break;
	}

	}


}


