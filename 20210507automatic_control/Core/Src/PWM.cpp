/*
 * pwm.cpp
 *
 *  Created on: May 4, 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Input:
 *
 *@Output:
 *
 *@How to use1:
 *1. input Input value into Function
 *2. you will get
 *
 *
 */
#include "Function.hpp"
#include "math.h"
#include "PWM.hpp"
#include "stdio.h"
#include <iostream>


double V1 = 0;
double V2 = 0;
double V3 = 0;
double V4 = 0;

double Vx = 0;
double Vy = 0;


void PWM::V_output(double V, double fai, double rotation_speed, double attitude_angle, bool stop)
{
	if( stop != true ){

		Function* function = new Function();

		Vx = V * cos(fai/180 * M_PI);
		Vy = V * sin(fai/180 * M_PI);

		attitude_angle = attitude_angle/180 * M_PI;



		V1 = Vx * cos( attitude_angle + M_PI/4) + Vy * sin( attitude_angle + M_PI/4) + rotation_speed;
		V2 = Vx * cos( attitude_angle + M_PI * 3/4) + Vy * sin( attitude_angle + M_PI * 3/4) + rotation_speed;
		V3 = Vx * cos( attitude_angle + M_PI * 5/4) + Vy * sin( attitude_angle + M_PI * 5/4) + rotation_speed;
		V4 = Vx * cos( attitude_angle + M_PI * 7/4) + Vy * sin( attitude_angle + M_PI * 7/4) + rotation_speed;

		uint8_t V1_pwm = (abs(V1) + 17.242) / 23.677;
		uint8_t V2_pwm = (abs(V2) + 17.242) / 23.677;
		uint8_t V3_pwm = (abs(V3) + 17.242) / 23.677;
		uint8_t V4_pwm = (abs(V4) + 17.242) / 23.677;


		function -> drive_motor(1, this -> plus_minus(V1), V1_pwm);
		function -> drive_motor(2, this -> plus_minus(V2), V2_pwm);
		function -> drive_motor(3, this -> plus_minus(V3), V3_pwm);
		function -> drive_motor(4, this -> plus_minus(V4), V4_pwm);


		delete function;

	}
	else{
		Function* function = new Function();

		function -> drive_motor(1, 3, 0);
		function -> drive_motor(2, 3, 0);
		function -> drive_motor(3, 3, 0);
		function -> drive_motor(4, 3, 0);

		delete function;

	}
}

uint8_t PWM::plus_minus(double number)
{
	if( number > 0 )
	{
		return 1;
	}
	if( number < 0 )
	{
		return 2;
	}
	if( number == 0 )
	{
		return 3;
	}

}


