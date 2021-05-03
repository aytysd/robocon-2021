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

void Motor::V_output(double V, double fai, double rotation_speed, double attitude_angle)
{
	Calc* calc = new Calc();

	double Vx = V * cos(fai/180 * M_PI);
	double Vy = V * sin(fai/180 * M_PI);



	double V1 = Vx * cos( attitude_angle + M_PI/4) + Vy * sin( attitude_angle + M_PI/4) + rotation_speed;
	double V2 = Vx * cos( attitude_angle + M_PI * 3/4) + Vy * sin( attitude_angle + M_PI * 3/4) + rotation_speed;
	double V3 = Vx * cos( attitude_angle + M_PI * 5/4) + Vy * sin( attitude_angle + M_PI * 5/4) + rotation_speed;
	double V4 = Vx * cos( attitude_angle + M_PI * 7/4) + Vy * sin( attitude_angle + M_PI * 7/4) + rotation_speed;


/*
	sprintf(output, "%lf\r\n%lf\r\n%lf\r\n%lf\r\n", V1,V2,V3,V4);
	HAL_UART_Transmit(&huart2, (uint8_t*)output, sizeof(output), 100);
*/





	this -> drive_motor(1, calc -> plus_minus(V1), (int)((abs(V1) * 1000 + 17.242) / 23.677));
	this -> drive_motor(2, calc -> plus_minus(V2), (int)((abs(V2) * 1000 + 17.242) / 23.677));
	this -> drive_motor(3, calc -> plus_minus(V3), (int)((abs(V3) * 1000 + 17.242) / 23.677));
	this -> drive_motor(4, calc -> plus_minus(V4), (int)((abs(V4) * 1000 + 17.242) / 23.677));


	delete calc;
}

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







