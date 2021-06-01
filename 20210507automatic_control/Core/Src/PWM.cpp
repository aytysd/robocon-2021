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



void PWM::V_output(double V, double fai, double rotation_speed, double attitude_angle, E_move_status status)
{
	if( status == E_move_status::MOVE ){

		Function* function = new Function();

		double Vx = V * cos(fai/180 * M_PI);
		double Vy = V * sin(fai/180 * M_PI);

		attitude_angle = attitude_angle/180 * M_PI;



		double V1 = Vx * cos( attitude_angle + M_PI/4) + Vy * sin( attitude_angle + M_PI/4) + rotation_speed;
		double V2 = Vx * cos( attitude_angle + M_PI * 3/4) + Vy * sin( attitude_angle + M_PI * 3/4) + rotation_speed;
		double V3 = Vx * cos( attitude_angle + M_PI * 5/4) + Vy * sin( attitude_angle + M_PI * 5/4) + rotation_speed;
		double V4 = Vx * cos( attitude_angle + M_PI * 7/4) + Vy * sin( attitude_angle + M_PI * 7/4) + rotation_speed;

		uint8_t V1_pwm = (abs(V1) + 17.242) / 23.677;
		uint8_t V2_pwm = (abs(V2) + 17.242) / 23.677;
		uint8_t V3_pwm = (abs(V3) + 17.242) / 23.677;
		uint8_t V4_pwm = (abs(V4) + 17.242) / 23.677;


		function -> drive_motor(1, this -> plus_minus(V1), V1_pwm, (uint16_t)(abs((double)V1)));
		function -> drive_motor(2, this -> plus_minus(V2), V2_pwm, (uint16_t)(abs((double)V1)));
		function -> drive_motor(3, this -> plus_minus(V3), V3_pwm, (uint16_t)(abs((double)V1)));
		function -> drive_motor(4, this -> plus_minus(V4), V4_pwm, (uint16_t)(abs((double)V1)));


		delete function;

	}
	else if( status == E_move_status::STOP ){
		Function* function = new Function();

		function -> drive_motor(1, 3, 0, 0);
		function -> drive_motor(2, 3, 0, 0);
		function -> drive_motor(3, 3, 0, 0);
		function -> drive_motor(4, 3, 0, 0);

		delete function;

	}
	else if( status == E_move_status::FREE ){
		Function* function = new Function();

		function -> drive_motor(1, 0, 0, 0);
		function -> drive_motor(2, 0, 0, 0);
		function -> drive_motor(3, 0, 0, 0);
		function -> drive_motor(4, 0, 0, 0);

		delete function;


	}
}

bool PWM::rotate(double V, uint16_t target_angle){

	Self_Pos::Gyro* gyro = new Self_Pos::Gyro();


	if( target_angle != gyro -> get_direction() ){

		int16_t diff = target_angle - gyro -> get_direction();

		if( target_angle > gyro -> get_direction() ){
			if( abs(diff) <= 180 ){
				this -> V_output(0, 0, -V, 0, E_move_status::MOVE);
				while( target_angle != gyro -> get_direction() ){

				}
				this -> V_output(0, 0, 0, 0, E_move_status::STOP);
				return true;
			}else{
				this -> V_output(0, 0, V, 0, E_move_status::MOVE);

				while( target_angle != gyro -> get_direction() ){

				}
				this -> V_output(0, 0, 0, 0, E_move_status::STOP);
				return true;

			}

		}else{

			if( abs(diff) <= 180 ){
				this -> V_output(0, 0, V, 0, E_move_status::MOVE);

				while( target_angle != gyro -> get_direction() ){

				}
				this -> V_output(0, 0, 0, 0, E_move_status::STOP);
				return true;

			}else{
				this -> V_output(0, 0, -V, 0, E_move_status::MOVE);

				while( target_angle != gyro -> get_direction() ){

				}
				this -> V_output(0, 0, 0, 0, E_move_status::STOP);
				return true;

			}

		}
	}else{
		return true;
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


