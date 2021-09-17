/*
 * Init_Move.cpp
 *
 *  Created on: 14 May 2021
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

#include <Error_Handling.hpp>
#include <Time.hpp>
#include "Init_Move.hpp"
#include "General_command.hpp"
#include "PWM.hpp"
#include "LED.hpp"
#include "Self_Pos.hpp"
#include "hGPIO.hpp"
#include "main.h"
#include "stdio.h"
#include "LED.hpp"
#include "Controller.hpp"
#include "Gyro.hpp"
#include "MPU6050.hpp"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "Control.hpp"
#include "Control_C.hpp"

bool Init_Move::SBDBT_OK = false;

void Init_Move::init_move( E_robot_name robot )
{

	LED* led = new LED();
	Control* control = new Control();
	Control_C* C = new Control_C();


	this -> Initialize( robot );
	led -> LED_output( E_LED_status::Init );
	HAL_Delay( 5000 );
	this -> SBDBT_Init( robot );

	if( robot == E_robot_name::C )
		C -> wait_for_ab();
	else
	{
		uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::ready };
		control -> send_command( E_robot_name::C, data );
	}


	delete led;
	delete control;
	delete C;

}

void Init_Move::Initialize( E_robot_name robot )
{

	  Gyro* gyro = new Gyro();
	  Self_Pos* self_pos = new Self_Pos();
	  MPU6050* mpu6050 = new MPU6050();
	  Time* time = new Time();

	  time -> reset_timer();

	  self_pos -> set_initial_pos( robot );
/*
	  gyro -> BNO055_Init_I2C( &hi2c1 );
	  gyro -> set_initial_direction( robot );
*/

	  if( robot != E_robot_name::C )
		  while( mpu6050 -> MPU6050_Init() == true );
	  mpu6050 -> set_initial_direction( robot );

	  HAL_UART_Receive_IT( &huart1, ( uint8_t* )&A_Rxdata_buff, sizeof( A_Rxdata_buff ) );
	  HAL_UART_Receive_IT( &huart5, ( uint8_t* )&B_Rxdata_buff, sizeof( B_Rxdata_buff ) );
	  HAL_UART_Receive_IT( &huart3, ( uint8_t* )&C_Rxdata_buff, sizeof( C_Rxdata_buff ) );
	  HAL_UART_Receive_IT( &huart4, ( uint8_t* )Controller::controller_Rxdata, sizeof( Controller::controller_Rxdata ) );

//	  HAL_TIM_Base_Start_IT( &htim6 );
	  HAL_TIM_Base_Start_IT( &htim3 );

	  HAL_TIM_Encoder_Start( &htim5, TIM_CHANNEL_ALL );
	  HAL_TIM_Encoder_Start( &htim2, TIM_CHANNEL_ALL );
	  HAL_TIM_Encoder_Start( &htim3, TIM_CHANNEL_ALL );

	  delete gyro;
	  delete self_pos;
	  delete mpu6050;
	  delete time;


}

void Init_Move::SBDBT_Init( E_robot_name robot )
{

	uint8_t test_data[ DATASIZE ] = { ( uint8_t )E_data_type::test, 10 };
	Control* control = new Control();

	switch( robot )
	{
	case E_robot_name::A:
	case E_robot_name::B:
#ifndef WITHOUT_C
		while( Init_Move::SBDBT_OK == false ){}
#endif
		break;
	case E_robot_name::C:

		uint32_t start_time = HAL_GetTick();
		while( ( HAL_GetTick() - start_time ) < 10000 )
		{
 			control -> send_command( E_robot_name::A, test_data );
			control -> send_command( E_robot_name::B, test_data );
			HAL_Delay( 1000 );
		}
		break;
	}

}



