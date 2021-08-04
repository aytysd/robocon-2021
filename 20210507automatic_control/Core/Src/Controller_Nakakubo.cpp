/*
 * Controller_new.cpp
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
#include "Function.hpp"
#include "Init_move.hpp"
#include "GPIO.hpp"
#include "main.h"

uint16_t Controller::speed = 700;
uint16_t Controller::speed_jump = 2400;


//--------------------------------------------------
//init
void Controller::NOP(void)
{
	PWM* pwm = new PWM();

	pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );

	delete pwm;
}


//--------------------------------------------------
//Jump
void Controller::X(void){}
void Controller::Y(void){}
void Controller::A(void){}
void Controller::B(void){}

void Controller::LB(void)
{
	Function* function = new Function();

	function -> drive_motor(5, CW, this -> speed_jump, false, true);
	while( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0 )
	{

	}
	while( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1)
	{

	}
	while( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0 )
	{

	}
	while( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1)
	{

	}
	function -> drive_motor(5, CW, this -> speed_jump - 500, false, true);
	while( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0 )
	{

	}
	function -> drive_motor(5, BRAKE, 0, false, true);

	delete function;
  /*
	Init_Move* init_move = new Init_Move();
	init_move -> init_move(E_robot_name::A);
	delete init_move;
  */
}


//--------------------------------------------------
//stop
void Controller::LT(void)
{
	Function* function = new Function();

	function -> drive_motor(1, BRAKE, 0, false, false);
	function -> drive_motor(2, BRAKE, 0, false, false);
	function -> drive_motor(3, BRAKE, 0, false, false);
	function -> drive_motor(4, BRAKE, 0, false, false);
	function -> drive_motor(5, BRAKE, 0, false, true);

	delete function;
}


//--------------------------------------------------
//reset
void Controller::RB(void)
{
	this -> speed = 500;
}
void Controller::RT(void)
{
	this -> speed_jump = 2000;
}


void Controller::START(void){}
void Controller::BACK(void){}



//--------------------------------------------------
//move in 8 direction
void Controller::CSR(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( this -> speed, 0, 0, 0, E_move_status::MOVE );

	  delete pwm;
}

void Controller::CSUR(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( this -> speed, 45, 0, 0, E_move_status::MOVE );

	  delete pwm;
}

void Controller::CSU(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( this -> speed, 90, 0, 0, E_move_status::MOVE );

	  delete pwm;
}
void Controller::CSUL(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( this -> speed, 135, 0, 0, E_move_status::MOVE );

	  delete pwm;
}
void Controller::CSL(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( this -> speed, 180, 0, 0, E_move_status::MOVE );

	  delete pwm;
}
void Controller::CSDL(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( this -> speed, 225, 0, 0, E_move_status::MOVE );

	  delete pwm;
}
void Controller::CSD(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( this -> speed, 270, 0, 0, E_move_status::MOVE );

	  delete pwm;
}
void Controller::CSDR(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( this -> speed, 315, 0, 0, E_move_status::MOVE );

	  delete pwm;
}


//--------------------------------------------------
//speed up and down
void Controller::RSU(void)
{
	this -> speed += 50;
	if(this -> speed > 1300)
	{
		this -> speed = 1300;
	}
}
void Controller::RSD(void)
{
	this -> speed -= 50;
	if(this -> speed < 700)
	{
		this -> speed = 700;
	}
}


//--------------------------------------------------
//rotation
void Controller::RSL(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 0, 0, -300, 0, E_move_status::MOVE );

	  delete pwm;
}

void Controller::RSR(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 0, 0, 300, 0, E_move_status::MOVE );

	  delete pwm;
}

void Controller::RSUL(void){}
void Controller::RSUR(void){}
void Controller::RSDR(void){}
void Controller::RSDL(void){}


//--------------------------------------------------
//speed_jump up and down
void Controller::LSU(void)
{
	this -> speed_jump += 50;
	if(this -> speed_jump > 2200)
	{
		this -> speed_jump = 2200;
	}
}

void Controller::LSD(void)
{
	this -> speed_jump -= 50;
	if(this -> speed_jump < 800)
	{
		this -> speed_jump = 800;
	}
}

void Controller::LSL(void){}
void Controller::LSR(void){}
void Controller::LSUL(void){}
void Controller::LSUR(void){}
void Controller::LSDR(void){}
void Controller::LSDL(void){}
