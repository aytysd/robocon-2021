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
#include "Gyro.hpp"
#include "Time.hpp"
#include "Debug.hpp"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "MPU6050.hpp"
#include "Line.hpp"
#include "Debug.hpp"

int16_t PWM::pre_dis_diff = 0;
int16_t PWM::pre_ang_diff = 0;

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

		function -> drive_motor(1, this -> plus_minus(V1), (uint16_t)(abs((double)V1)), true, false);
		function -> drive_motor(2, this -> plus_minus(V2), (uint16_t)(abs((double)V2)), true, false);
		function -> drive_motor(3, this -> plus_minus(V3), (uint16_t)(abs((double)V3)), true, false);
		function -> drive_motor(4, this -> plus_minus(V4), (uint16_t)(abs((double)V4)), true, false);



		delete function;

	}
	else if( status == E_move_status::STOP )
	{


		Function* function = new Function();

		function -> drive_motor(1, 3, 0, false, false);
		function -> drive_motor(2, 3, 0, false, false);
		function -> drive_motor(3, 3, 0, false, false);
		function -> drive_motor(4, 3, 0, false, false);


		delete function;

	}
}

void PWM::Front_Move( uint16_t V, uint16_t fai, uint16_t attitude_angle, double Line_dis_diff, E_move_status status)
{
	if( status == E_move_status::MOVE)
	{
		int16_t dis_angle = fai - attitude_angle;
		if( dis_angle > 180 )
		{
			dis_angle = dis_angle - 360;
		}
		else if( dis_angle < -180 )
		{
			dis_angle = 360 + dis_angle;
		}

		int16_t dev_dis =  ( int16_t )Line_dis_diff - pre_dis_diff;
		pre_dis_diff = ( int16_t )Line_dis_diff;

		int16_t ang_dis = ( int16_t )dis_angle - pre_dis_diff;
		pre_dis_diff = ( int16_t )dis_angle;

		int16_t delta_V =  ( int16_t )Line_dis_diff * dis_diff_Kp/* + dev_dis * dis_diff_Kd + dis_angle * ang_diff_Kp + ang_dis * ang_diff_Kd*/;


/*
 *        3         Front        2
 *          --------------------
 *          |                  |
 *          |                  |
 *          |                  |
 *          |                  |
 *          |				   |
 *          |				   |
 *          | 				   |
 *          |                  |
 *          --------------------
 *        4                      1
 */


		int16_t V_2_1 = ( int16_t )V + delta_V;
		int16_t V_3_4 = ( int16_t )V - delta_V;



		if( V_2_1 < 0)
		{
			Function* function = new Function();

			function -> drive_motor( 1, CCW, abs( V_2_1 ), true, false );
			function -> drive_motor( 2, CCW, abs( V_2_1 ), true, false );
			function -> drive_motor( 3, CCW, V_3_4, true, false );
			function -> drive_motor( 4, CCW, V_3_4, true, false );

			delete function;
		}
		else if( V_3_4 < 0 )
		{
			Function* function = new Function();

			function -> drive_motor( 1,  CW, V_2_1, true, false );
			function -> drive_motor( 2,  CW, V_2_1, true, false );
			function -> drive_motor( 3,  CW, abs( V_3_4 ), true, false );
			function -> drive_motor( 4,  CW, abs( V_3_4 ), true, false );

			delete function;
		}
		else
		{
			Function* function = new Function();


			function -> drive_motor( 1,  CW, V_2_1, true, false );
			function -> drive_motor( 2,  CW, V_2_1, true, false );
			function -> drive_motor( 3, CCW, V_3_4, true, false );
			function -> drive_motor( 4, CCW, V_3_4, true, false );

//			function -> drive_motor( 1,  CW, 500, true, false );
//			function -> drive_motor( 2,  CW, 500, true, false );
//			function -> drive_motor( 3, CCW, 500, true, false );
//			function -> drive_motor( 4, CCW, 500, true, false );


			delete function;
		}
	}
	else if( status == E_move_status::STOP)
	{
		Function* function = new Function();

		function -> drive_motor( 1, BRAKE, 0, false, false );
		function -> drive_motor( 2, BRAKE, 0, false, false );
		function -> drive_motor( 3, BRAKE, 0, false, false );
		function -> drive_motor( 4, BRAKE, 0, false, false );

		delete function;
	}
 }

bool PWM::rotate(uint16_t V, uint16_t target_angle)
{

	MPU6050* gyro = new MPU6050();
	Debug::TTO_val( 0, "rotate:");

	if( !( abs(  target_angle - ( uint16_t )gyro -> get_direction( &hi2c1 ) ) < 3 ) )
	{

		int16_t diff = target_angle - gyro -> get_direction( &hi2c1 );
		while( diff < 0 )
			diff += 360;

		if( diff >= 180 )
		{
			Line::Enable_line = false;
			this -> V_output(0, 0, -V, 0, E_move_status::MOVE);
			Debug::TTO_val(0, "180 to 360:" );
			Debug::time_calc();
			while( !( abs(  target_angle - ( uint16_t )gyro -> get_direction( &hi2c1 ) ) < 3 ) )
			{
				gyro -> MPU6050_update_Gyro( &hi2c1 );
				HAL_Delay( 100 );
			}


			Debug::time_calc();
			this -> V_output(0, 0, 0, 0, E_move_status::STOP);
			Line::Enable_line = true;

		}
		else
		{
			Line::Enable_line = false;
			this -> V_output(0, 0, +V, 0, E_move_status::MOVE);
			Debug::TTO_val(0, "0 to 180:" );
			Debug::time_calc();
			while( !( abs(  target_angle - ( uint16_t )gyro -> get_direction( &hi2c1 ) ) < 3 ) )
			{
				gyro -> MPU6050_update_Gyro( &hi2c1 );
				HAL_Delay( 100 );

			}
			Debug::time_calc();
			this -> V_output(0, 0, 0, 0, E_move_status::STOP);
			Line::Enable_line = true;

		}

	}


	delete gyro;
	return true;
}




uint8_t PWM::plus_minus( int16_t number )
{
	if( number > 0 ) return CW;
	else if( number < 0 ) return CCW;
	else if( number == 0 ) return BRAKE;

}


