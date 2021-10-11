/*
 * Controller_Yoshida.cpp
 *
 *  Created on: Jul 4, 2021
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

#include "Controller.hpp"
#include "PWM.hpp"
#include "Function.hpp"
#include "Rope.hpp"
#include "usart.h"
#include "Jump.hpp"
#include "Function.hpp"

bool Controller::Is_entered = false;
uint16_t Controller::speed = 600;
#define SPEED_JUMP 1000

bool Controller::jump_enable = false;
bool Controller::move_ok = false;
bool Controller::rotating = false;

PWM* pwm = new PWM();

void Controller::NOP(void)
{
	if( ROBOT != E_robot_name::C )
	{
		  pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );

	}
}

void Controller::X(void){}
void Controller::Y(void)
{
	Controller::move_ok = true;
}
void Controller::A(void){}
void Controller::B(void)
{
	Controller::move_ok = false;
	pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );
	HAL_GPIO_WritePin( GPIOC, GPIO_PIN_2, GPIO_PIN_RESET );
}

void Controller::LB(void){}
void Controller::RB(void)
{
	Controller::jump_enable = true;
}
void Controller::LT(void)
{
	Controller::speed = SPEED_JUMP;
}
void Controller::RT(void)
{
	Controller::speed = 600;
}
void Controller::START(void)
{

		Function* function = new Function();
		function -> drive_motor( 1, CW, 270, false, false );
		delete function;

}
void Controller::BACK(void)
{
		Function* function = new Function();
		function -> drive_motor( 1, BRAKE, 270, false, false );
		delete function;

}

void Controller::LSU(void)
{
	pwm -> V_output( Controller::speed, 90, 0, 0, E_move_status::MOVE );

}
void Controller::LSL(void)
{
	pwm -> V_output( Controller::speed, 180, 0, 0, E_move_status::MOVE );
}
void Controller::LSR(void)
{
	pwm -> V_output( Controller::speed, 0, 0, 0, E_move_status::MOVE );

}
void Controller::LSD(void)
{
	pwm -> V_output( Controller::speed, 270, 0, 0, E_move_status::MOVE );

}
void Controller::LSUL(void)
{
	pwm -> V_output( Controller::speed, 135, 0, 0, E_move_status::MOVE );

}
void Controller::LSUR(void)
{
	pwm -> V_output( Controller::speed, 45, 0, 0, E_move_status::MOVE );

}
void Controller::LSDR(void)
{
	pwm -> V_output( Controller::speed, 315, 0, 0, E_move_status::MOVE );

}
void Controller::LSDL(void)
{
	pwm -> V_output( Controller::speed, 225, 0, 0, E_move_status::MOVE );
}


void Controller::CSU(void){}
void Controller::CSR(void){}
void Controller::CSL(void){}
void Controller::CSD(void){}
void Controller::CSUL(void){}
void Controller::CSUR(void){}
void Controller::CSDL(void){}
void Controller::CSDR(void){}


void Controller::RSU(void)
{
	Controller::speed += 100;
}
void Controller::RSR(void)
{
	pwm -> V_output( 0, 0, 300, 0, E_move_status::MOVE );
	Controller::rotating = true;
}
void Controller::RSL(void)
{
	pwm -> V_output( 0, 0, -300, 0, E_move_status::MOVE );
	Controller::rotating = true;
}
void Controller::RSD(void)
{
	Controller::speed -= 100;
}
void Controller::RSUL(void){}
void Controller::RSUR(void){}
void Controller::RSDR(void){}
void Controller::RSDL(void){}

