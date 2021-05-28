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

#include "Init_Move.hpp"
#include "General_command.hpp"
#include "PWM.hpp"
#include "Wait.hpp"
#include "LED.hpp"
#include "Self_Pos.hpp"
#include "GPIO.hpp"
#include "Controller.hpp"

class Wait : public Super_Wait{
public:

	bool wait_F(){

		GPIO* gpio = new GPIO();

		while( true != gpio -> get_status( E_interrupt::LIMIT_F_V2 )){

		}
		while( true != gpio -> get_status( E_interrupt::LIMIT_F_V3 )){

		}

		delete gpio;

		return true;
	}

	bool wait_L(){

		GPIO* gpio = new GPIO();

		while( true != gpio -> get_status( E_interrupt::LIMIT_L_V3 )){

		}
		while( true != gpio -> get_status( E_interrupt::LIMIT_L_V4 )){

		}

		delete gpio;

		return true;

	}

	bool wait_connection(){

		return true;
	}
};


void Init_Move::init_move(E_robot_name robot){

	PWM* pwm = new PWM();
	Wait* wait = new Wait();
	LED_Mode* led = new LED_Mode();

	led -> LED_output(E_LED_status::Init);

	switch(robot){
	case E_robot_name::A:
		pwm -> V_output(100, 90, 0, 0, E_move_status::MOVE);
		wait -> wait_F();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);
		HAL_Delay(3000);

		pwm -> V_output(100, 180, 0, 0, E_move_status::MOVE);
		wait -> wait_L();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);

		break;
	case E_robot_name::B:
		pwm -> V_output(100, 180, 0, 90, E_move_status::MOVE);
		wait -> wait_F();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);
		HAL_Delay(3000);

		pwm -> V_output(100, 270, 0, 90, E_move_status::MOVE);
		wait -> wait_L();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);

		break;
	case E_robot_name::C:
		pwm -> V_output(100, 270, 0, 180, E_move_status::MOVE);
		wait -> wait_F();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);
		HAL_Delay(3000);

		pwm -> V_output(100, 360, 0, 180, E_move_status::MOVE);
		wait -> wait_L();
		pwm -> V_output(0, 0, 0, 0, E_move_status::STOP);

		break;
	}

	this -> Initialize();

	delete led;
	delete pwm;
	delete wait;

}

void Init_Move::Initialize(){

	  Self_Pos::Gyro* gyro = new Self_Pos::Gyro();
	  Self_Pos* self_pos = new Self_Pos();

	  self_pos -> set_initial_pos(E_robot_name::A);
	  gyro-> BNO055_Init_I2C(&hi2c1);
	  gyro -> set_initial_direction(E_robot_name::A);

	  HAL_UART_Receive_IT(&huart4, (uint8_t*)Controller::controller_Rxdata, sizeof(Controller::controller_Rxdata));

	  HAL_TIM_Base_Start_IT(&htim6);

	  HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
	  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

	  delete gyro;
	  delete self_pos;



}

