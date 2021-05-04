/*
 * pwm.cpp
 *
 *  Created on: May 3, 2021
 *      Author: Ayato Yoshida
 */



#include <Calc.hpp>
#include <Motor.hpp>
#include "math.h"
#include "main.h"
#include "stdio.h"

char output[256];


void Motor::drive_motor(int motor_number, int direction, int PWM)
{
	int motor[2] = { (1<<6) | (motor_number<<2) | direction, PWM};
	for(int i = 0; i<2; i++)
	{
		sprintf(output, "%d\r\n", motor[i]);
		HAL_UART_Transmit(&huart2, (uint8_t*)output, sizeof(output), 100);

	}

//	HAL_UART_Transmit(&huart6, (uint8_t*)motor, sizeof(motor), 100);
}







