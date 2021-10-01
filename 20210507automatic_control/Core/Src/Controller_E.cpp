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
#include "MPU6050.hpp"
#include "usart.h"
#include "Jump.hpp"
#include "Control_B.hpp"
#include "Control.hpp"

bool Controller::Is_entered = false;
uint16_t Controller::speed = 400;
uint16_t Controller::speed_jump = 1000;

bool Controller::jump_enable = false;
bool Controller::move_ok = false;

PWM* pwm = new PWM();

void Controller::NOP(void)
{
	  pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );
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
}

void Controller::LB(void){}
void Controller::RB(void)
{
	Controller::jump_enable = true;
}
void Controller::LT(void){}
void Controller::RT(void){}
void Controller::START(void)
{
	Controller::speed = Controller::speed_jump;
}
void Controller::BACK(void){}

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
}
void Controller::RSL(void)
{
	pwm -> V_output( 0, 0, -300, 0, E_move_status::MOVE );
}
void Controller::RSD(void)
{
	Controller::speed -= 100;
}
void Controller::RSUL(void){}
void Controller::RSUR(void){}
void Controller::RSDR(void){}
void Controller::RSDL(void){}

