/*
 * Function.cpp
 *
 *  Created on: 7 May 2021
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


#include <Function.hpp>
#include "main.h"
#include "stdio.h"

void Function::drive_motor(uint8_t motor_number, uint8_t direction, uint8_t PWM)
{
	uint8_t motor[2] = {(1<<6) | (motor_number<<2) | direction, PWM};
/*
	for(int i = 0; i<3; i++)
	{
		sprintf(output, "%d\r\n", motor[i]);
		HAL_UART_Transmit(&huart2, (uint8_t*)output, sizeof(output), 100);

	}
*/

	HAL_UART_Transmit(&huart6, (uint8_t*)motor, sizeof(motor), 100);
}
void Function::drive_solenoid_valve( int port_number, int ON_OFF)
{

	uint8_t solenoid_valve = (port_number<<1)|ON_OFF;

/*
		sprintf(output, "%d\r\n", solenoid_valve);
		HAL_UART_Transmit(&huart2, (uint8_t*)output, sizeof(output), 100);
*/

	HAL_UART_Transmit(&huart3, (uint8_t*)&solenoid_valve, sizeof(solenoid_valve), 100);
}



