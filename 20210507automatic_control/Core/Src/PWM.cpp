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
#include "General_command.hpp"
#include "Self_Pos.hpp"



void PWM::V_output(uint16_t V, uint16_t fai, int16_t rotation_speed, uint16_t attitude_angle, E_move_status status)
{
	if( status == E_move_status::MOVE )
	{

		Function* function = new Function();

		double Vx = V * cos( ( (double)fai / (double)180 ) * M_PI );
		double Vy = V * sin( ( (double)fai / (double)180 ) * M_PI );

		double attitude_rad = (double)attitude_angle / (double)180 * M_PI;



		double V1 = Vx * cos( attitude_rad + M_PI/4) + Vy * sin( attitude_rad + M_PI/4) + (double)rotation_speed;
		double V2 = Vx * cos( attitude_rad + M_PI * 3/4) + Vy * sin( attitude_rad + M_PI * 3/4) + (double)rotation_speed;
		double V3 = Vx * cos( attitude_rad + M_PI * 5/4) + Vy * sin( attitude_rad + M_PI * 5/4) + (double)rotation_speed;
		double V4 = Vx * cos( attitude_rad + M_PI * 7/4) + Vy * sin( attitude_rad + M_PI * 7/4) + (double)rotation_speed;

		function -> drive_motor(1, this -> plus_minus(V1), (uint16_t)(abs((double)V1)), true);
		function -> drive_motor(2, this -> plus_minus(V2), (uint16_t)(abs((double)V2)), true);
		function -> drive_motor(3, this -> plus_minus(V3), (uint16_t)(abs((double)V3)), true);
		function -> drive_motor(4, this -> plus_minus(V4), (uint16_t)(abs((double)V4)), true);


		delete function;

	}
	else if( status == E_move_status::STOP )
	{
		Function* function = new Function();

		function -> drive_motor(1, 3, 0, false);
		function -> drive_motor(2, 3, 0, false);
		function -> drive_motor(3, 3, 0, false);
		function -> drive_motor(4, 3, 0, false);

		delete function;

	}
}

bool PWM::rotate(uint16_t V, uint16_t target_angle)
{

	Self_Pos::Gyro* gyro = new Self_Pos::Gyro();


	if( target_angle != gyro -> get_direction() )
	{

		int16_t diff = target_angle - gyro -> get_direction();

		if( target_angle > gyro -> get_direction() )
		{
			if( abs(diff) <= 180 )
			{
				this -> V_output(0, 0, -V, 0, E_move_status::MOVE);
				while( target_angle != gyro -> get_direction() ){}
				this -> V_output(0, 0, 0, 0, E_move_status::STOP);

				delete gyro;
				return true;
			}
			else
			{
				this -> V_output(0, 0, V, 0, E_move_status::MOVE);
				while( target_angle != gyro -> get_direction() ){}
				this -> V_output(0, 0, 0, 0, E_move_status::STOP);

				delete gyro;
				return true;

			}

		}
		else
		{

			if( abs(diff) <= 180 )
			{
				this -> V_output(0, 0, V, 0, E_move_status::MOVE);
				while( target_angle != gyro -> get_direction() ){}
				this -> V_output(0, 0, 0, 0, E_move_status::STOP);

				delete gyro;
				return true;

			}
			else
			{
				this -> V_output(0, 0, -V, 0, E_move_status::MOVE);
				while( target_angle != gyro -> get_direction() ){}
				this -> V_output(0, 0, 0, 0, E_move_status::STOP);

				delete gyro;
				return true;

			}

		}
	}
	else
	{
		delete gyro;
		return true;
	}

}

uint8_t PWM::plus_minus(double number)
{
	if( number > 0 )
	{
		return CW;
	}
	if( number < 0 )
	{
		return CCW;
	}
	if( number == 0 )
	{
		return BRAKE;
	}



}


