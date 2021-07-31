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
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "Control.hpp"


void Init_Move::init_move( E_robot_name robot )
{

	LED* led = new LED();

	led -> LED_output( E_LED_status::Init );

	while( ( HAL_GPIO_ReadPin( LIMIT_F_V2_GPIO_Port, LIMIT_F_V2_Pin ) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_F_V3_GPIO_Port, LIMIT_F_V3_Pin ) == GPIO_PIN_RESET ) ){}
	while( ( HAL_GPIO_ReadPin( LIMIT_L_V3_GPIO_Port, LIMIT_L_V3_Pin ) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_L_V4_GPIO_Port, LIMIT_L_V4_Pin ) == GPIO_PIN_RESET ) ){}

	this -> Initialize( robot );

	led -> LED_output( E_LED_status::Done );

	if( robot == E_robot_name::C )
	{
		Control* control = new Control();

		uint8_t data[4] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MOVE_INFINITY_INITIAL_POS, 0, 0 };

		control -> send_command( E_robot_name::A, data );
		control -> send_command( E_robot_name::B, data );

		delete control;

	}

	delete led;

}

void Init_Move::Initialize( E_robot_name robot )
{

	  Gyro* gyro = new Gyro();
	  Self_Pos* self_pos = new Self_Pos();
	  MPU6050* mpu6050 = new MPU6050();

	  self_pos -> set_initial_pos( robot );
/*
	  gyro -> BNO055_Init_I2C( &hi2c1 );
	  gyro -> BNO055_Init_I2C( &hi2c3 );
*/
//	  gyro -> set_initial_direction( robot );

	  mpu6050 -> MPU6050_Init( &hi2c1 );
	  mpu6050 -> MPU6050_Init( &hi2c3 );

	  mpu6050 -> set_initial_direction( robot );

	  __HAL_UART_ENABLE_IT( &huart4, UART_IT_RXNE );
	  __HAL_UART_ENABLE_IT( &huart3, UART_IT_RXNE );
	  __HAL_UART_ENABLE_IT( &huart1, UART_IT_RXNE );

/*
	  __HAL_UART_DISABLE_IT( &huart3 , UART_IT_RXNE );
	  __HAL_UART_DISABLE_IT( &huart4 , UART_IT_RXNE );
	  __HAL_UART_DISABLE_IT( &huart1 , UART_IT_RXNE );
*/
/*
	  HAL_UART_Receive_IT(&huart1, (uint8_t*)Communication::Rxdata, sizeof(Communication::Rxdata));
	  HAL_UART_Receive_IT(&huart4, (uint8_t*)Controller::controller_Rxdata, sizeof(Controller::controller_Rxdata));
	  HAL_UART_Receive_IT(&huart3, (uint8_t*)Communication::Rxdata, sizeof(Communication::Rxdata));
*/


	  HAL_TIM_Base_Start_IT( &htim6 );
//	  HAL_TIM_Base_Start_IT( &htim7 );
	  HAL_TIM_Base_Start_IT( &htim3 );
	  HAL_TIM_Base_Start_IT( &htim4 );

	  HAL_TIM_Encoder_Start( &htim5, TIM_CHANNEL_ALL );
	  HAL_TIM_Encoder_Start( &htim2, TIM_CHANNEL_ALL );
	  HAL_TIM_Encoder_Start( &htim3, TIM_CHANNEL_ALL );
	  HAL_TIM_Encoder_Start( &htim4, TIM_CHANNEL_ALL );

	  delete gyro;
	  delete self_pos;
	  delete mpu6050;



}

