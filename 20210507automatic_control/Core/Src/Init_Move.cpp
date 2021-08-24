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


void Init_Move::init_move( E_robot_name robot )
{

	LED* led = new LED();
	Control* control = new Control();


	led -> LED_output( E_LED_status::Init );

	while( HAL_GPIO_ReadPin( LIMIT_F_V2_GPIO_Port, LIMIT_F_V2_Pin ) == GPIO_PIN_SET ){}
	while( HAL_GPIO_ReadPin( LIMIT_L_V3_GPIO_Port, LIMIT_L_V3_Pin ) == GPIO_PIN_SET ){}

	this -> Initialize( robot );



	if( robot == E_robot_name::C )
	{

#ifdef WITHOUT_B
		while( !( Control::A_done_flag == true && Control::B_done_flag == true ) ){}

		Control::A_done_flag = false;
		Control::B_done_flag = false;

		led -> LED_output( E_LED_status::Done );


		uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MOVE_INFINITY_INITIAL_POS, 0, 0 };

		control -> send_command( E_robot_name::A, data );
		control -> send_command( E_robot_name::B, data );
#else
		while( !( Control::A_done_flag == true ) ){}

		Control::A_done_flag = false;

		led -> LED_output( E_LED_status::Done );

		uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MOVE_INFINITY_INITIAL_POS, 0, 0 };
		control -> send_command( E_robot_name::A, data );
#endif

	}
	else
	{
		uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::done };
		control -> send_command( E_robot_name::C, data );
	}


	delete led;
	delete control;


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
	  gyro -> BNO055_Init_I2C( &hi2c3 );
*/
//	  gyro -> set_initial_direction( robot );

	  while( mpu6050 -> MPU6050_Init( &hi2c1 ) == true );
	  while( mpu6050 -> MPU6050_Init( &hi2c3 ) == true );
	  mpu6050 -> set_initial_direction( robot );


	  HAL_UART_Receive_IT( &huart1, ( uint8_t* )A_Rxdata_buff, sizeof( A_Rxdata_buff ) );
	  HAL_UART_Receive_IT( &huart5, ( uint8_t* )B_Rxdata_buff, sizeof( B_Rxdata_buff ) );
	  HAL_UART_Receive_IT( &huart3, ( uint8_t* )C_Rxdata_buff, sizeof( C_Rxdata_buff ) );
	  HAL_UART_Receive_IT( &huart4, ( uint8_t* )Controller::controller_Rxdata, sizeof( Controller::controller_Rxdata ) );

	  HAL_TIM_Base_Start_IT( &htim6 );
	  HAL_TIM_Base_Start_IT( &htim3 );

	  HAL_TIM_Encoder_Start( &htim5, TIM_CHANNEL_ALL );
	  HAL_TIM_Encoder_Start( &htim2, TIM_CHANNEL_ALL );
	  HAL_TIM_Encoder_Start( &htim3, TIM_CHANNEL_ALL );

	  delete gyro;
	  delete self_pos;
	  delete mpu6050;
	  delete time;


}

