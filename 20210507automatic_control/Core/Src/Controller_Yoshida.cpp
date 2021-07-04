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


/*
void Controller::NOP(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );

	  delete pwm;


	  this -> speed = 0;



}

void Controller::X(void)
{
	this -> speed -= 100;
}
void Controller::Y(void)
{
	this -> direction += 10;
}
void Controller::A(void)
{
	this -> direction -= 10;
}
void Controller::B(void)
{
	this -> speed += 100;
}

void Controller::LB(void){}
void Controller::RB(void){}
void Controller::LT(void){}
void Controller::RT(void){}
void Controller::START(void){}
void Controller::BACK(void){}

void Controller::LSU(void){}
void Controller::LSL(void){}
void Controller::LSR(void){}
void Controller::LSD(void){}

void Controller::CSU(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 500, 90, 0, 0, E_move_status::MOVE );

	  delete pwm;

}
void Controller::CSR(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( this -> speed, 0, 0, 0, E_move_status::MOVE );

	  delete pwm;


}
void Controller::CSL(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( this -> speed, 180, 0, 0, E_move_status::MOVE );

	  delete pwm;


}
void Controller::CSD(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( this -> speed, 270, 0, 0, E_move_status::MOVE );

	  delete pwm;

}

void Controller::RSU(void){}
void Controller::RSR(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 0, 0, 500, 0, E_move_status::MOVE );

	  delete pwm;

}
void Controller::RSL(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 0, 0, -500, 0, E_move_status::MOVE );

	  delete pwm;

}
void Controller::RSD(void){}
*/