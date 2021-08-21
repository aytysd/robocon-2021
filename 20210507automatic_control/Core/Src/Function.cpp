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
#include "math.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


void Function::drive_motor(uint8_t motor_number, uint8_t direction, uint16_t speed, bool PID_Enabled, bool Jump_Enabled )
{
	uint8_t PWM = speed / 23.677;

	uint8_t speed_p = ( speed & 0b1111111100000000 ) >> 8;
	uint8_t speed_q = ( speed & 0b0000000011111111 );
	uint8_t motor[4] = { ( motor_number << 2 ) | direction, PWM, speed_p, speed_q };

	if( PID_Enabled == true ) motor[0] |= ( 0b01 << 6 );
	if( Jump_Enabled == true ) motor[0] |= ( 0b01 << 7 );

	HAL_UART_Transmit( &huart6, ( uint8_t* )motor, sizeof( motor ), 100 );
}
void Function::drive_solenoid_valve( uint8_t port_number, uint8_t ON_OFF )
{

	uint8_t solenoid_valve = ( port_number << 1 ) | ON_OFF;
	HAL_UART_Transmit( &huart3, ( uint8_t* )&solenoid_valve, sizeof( solenoid_valve ), 100 );
}

void Function::drive_LED( uint8_t g, uint8_t r, uint8_t b, uint8_t w )
{
	uint8_t LED[ 4 ] = { g, r, b, w };
	HAL_UART_Transmit( &huart5, ( uint8_t* )LED, sizeof( LED ), 100 );
}

void Function::drive_motor_Rope( uint8_t motor_number, uint8_t direction, uint16_t angular_velocity, bool PID_Enabled )
{
	double rad_velocity = ( ( double )angular_velocity / ( double )180 ) * M_PI;
	uint16_t speed = rad_velocity * OMNI_RADIUS;

	uint8_t PWM = speed / 23.677;

	uint8_t speed_p = ( speed & 0b1111111100000000 ) >> 8;
	uint8_t speed_q = ( speed & 0b0000000011111111 );
	uint8_t motor[4] = { ( motor_number << 2 ) | direction, PWM, speed_p, speed_q};

	if( PID_Enabled == true ) motor[0] |= ( 0b01 << 6 );

	HAL_UART_Transmit( &huart6, ( uint8_t* )motor, sizeof( motor ), 100 );
}

