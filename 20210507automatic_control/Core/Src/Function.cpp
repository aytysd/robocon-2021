/*
 * Function.cpp
 *
 *  Created on: 7 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(not activate motor and solenoid valve)
 *
 *@Input(the motor number you want to use)in(motor_number)of(drive_motor)
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

void Function::drive_motor(uint8_t motor_number, uint8_t direction, uint8_t PWM, uint16_t speed, bool PID_Enabled)
{
	uint8_t speed_p = ( speed & 0b1111111100000000 ) >> 8;
	uint8_t speed_q = ( speed & 0b0000000011111111 );
	uint8_t motor[4] = { (motor_number<<2) | direction, PWM, speed_p, speed_q};

	if( PID_Enabled == true )
	{
		motor[0] |= ( 0b01 << 6 );
	}

	HAL_UART_Transmit(&huart6, (uint8_t*)motor, sizeof(motor), 100);
}
void Function::drive_solenoid_valve( int port_number, int ON_OFF)
{

	uint8_t solenoid_valve = (port_number<<1) | ON_OFF;
	HAL_UART_Transmit(&huart3, (uint8_t*)&solenoid_valve, sizeof(solenoid_valve), 100);
}

void Function::drive_LED(int color, int brightness)
{
	uint8_t LED = (color << 6) | brightness;
	HAL_UART_Transmit(&huart5, &LED, sizeof(LED), 3000);
}



