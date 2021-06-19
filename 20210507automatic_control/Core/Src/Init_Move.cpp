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
#include "Init_Move.hpp"
#include "General_command.hpp"
#include "PWM.hpp"
#include "Super_Wait.hpp"
#include "LED.hpp"
#include "Self_Pos.hpp"
#include "GPIO.hpp"
#include "main.h"
#include "stdio.h"
#include "Flow.hpp"
#include "Communication.hpp"
#include "LED.hpp"

namespace Init_Wait
{

class Wait : public Super_Wait
{
public:

	bool wait_F()
	{

		Error_Handling::current_func = const_cast<char*>(__func__);
		Error_Handling::current_line = __LINE__;

		Error_Handling* error_handling = new Error_Handling();

		while( (HAL_GPIO_ReadPin(LIMIT_F_V2_GPIO_Port, LIMIT_F_V2_Pin) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_F_V3_GPIO_Port, LIMIT_F_V3_Pin ) == GPIO_PIN_RESET))
		{
			static uint32_t start_time = HAL_GetTick();

			if( HAL_GetTick() - start_time >= 3000 )
			{
			Error_Handling::error_line = __LINE__;
			Error_Handling::error_func = __func__;
			error_handling -> set_flag( E_Errors::Init_move_failed );
			Error_Handler();

			}


		}
		delete error_handling;

		return true;
	}

	bool wait_L()
	{

		Error_Handling::current_func = const_cast<char*>(__func__);
		Error_Handling::current_line = __LINE__;

		Error_Handling* error_handling = new Error_Handling();


		while( (HAL_GPIO_ReadPin(LIMIT_L_V3_GPIO_Port, LIMIT_L_V3_Pin) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_L_V4_GPIO_Port, LIMIT_L_V4_Pin ) == GPIO_PIN_RESET))
		{
			static uint32_t start_time = HAL_GetTick();

			if( HAL_GetTick() - start_time >= 3000 )

			{
			Error_Handling::error_line = __LINE__;
			Error_Handling::error_func = __func__;
			error_handling -> set_flag( E_Errors::Init_move_failed );
			Error_Handler();

			}


		}

		delete error_handling;
		return true;

	}

	bool wait_connection()
	{
		Error_Handling::current_func = const_cast<char*>(__func__);
		Error_Handling::current_line = __LINE__;

		return true;
	}
};

}


void Init_Move::init_move(E_robot_name robot)
{

	PWM* pwm = new PWM();
	Init_Wait::Wait* wait = new Init_Wait::Wait();
	LED* led = new LED();

	led -> LED_output(E_LED_status::Init);

	switch(robot)
	{
	case E_robot_name::A:

		Error_Handling::current_func = const_cast<char*>(__func__);
		Error_Handling::current_line = __LINE__;

		pwm -> V_output(100, 90, 0, 0, E_move_status::MOVE);
		wait -> wait_F();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);
		HAL_Delay(3000);

		pwm -> V_output(100, 180, 0, 0, E_move_status::MOVE);
		wait -> wait_L();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);

		break;
	case E_robot_name::B:

		Error_Handling::current_func = const_cast<char*>(__func__);
		Error_Handling::current_line = __LINE__;

		pwm -> V_output(100, 180, 0, 90, E_move_status::MOVE);
		wait -> wait_F();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);
		HAL_Delay(3000);

		pwm -> V_output(100, 270, 0, 90, E_move_status::MOVE);
		wait -> wait_L();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);

		break;
	case E_robot_name::C:

		Error_Handling::current_func = const_cast<char*>(__func__);
		Error_Handling::current_line = __LINE__;

		pwm -> V_output(100, 270, 0, 180, E_move_status::MOVE);
		wait -> wait_F();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);
		HAL_Delay(3000);

		pwm -> V_output(100, 360, 0, 180, E_move_status::MOVE);
		wait -> wait_L();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);

		break;
	}

	Error_Handling::current_func = const_cast<char*>(__func__);
	Error_Handling::current_line = __LINE__;



	this -> Initialize(robot);

	delete led;
	delete pwm;
	delete wait;

	led -> LED_output(E_LED_status::Done);

}

void Init_Move::Initialize(E_robot_name robot)
{

	  Self_Pos::Gyro* gyro = new Self_Pos::Gyro();
	  Self_Pos* self_pos = new Self_Pos();

	  self_pos -> set_initial_pos(robot);
	  gyro -> BNO055_Init_I2C(&hi2c1);
	  gyro -> set_initial_direction(robot);

	  HAL_UART_Receive_IT(&huart1, (uint8_t*)Communication::Rxdata, sizeof(Communication::Rxdata));


	  HAL_TIM_Base_Start_IT(&htim6);
	  HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
	  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

	  delete gyro;
	  delete self_pos;



}

