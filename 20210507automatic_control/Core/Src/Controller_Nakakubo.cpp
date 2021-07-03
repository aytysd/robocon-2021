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

/*
void Controller::footwork(uint8_t direction, uint16_t speed)
{
	uint8_t pwm = speed / 23.677;
	Function* function = new Function();
	if(direction == 1)
	{
		function -> drive_motor(1, 2, pwm, speed, true);
		function -> drive_motor(2, 2, pwm, speed, true);
		function -> drive_motor(3, 1, pwm, speed, true);
		function -> drive_motor(4, 1, pwm, speed, true);
	}
	else if(direction == 2)
	{
		function -> drive_motor(1, 2, pwm, speed, true);
		function -> drive_motor(2, 1, pwm, speed, true);
		function -> drive_motor(3, 1, pwm, speed, true);
		function -> drive_motor(4, 2, pwm, speed, true);
	}
	else if(direction == 3)
	{
		function -> drive_motor(1, 1, pwm, speed, true);
		function -> drive_motor(2, 1, pwm, speed, true);
		function -> drive_motor(3, 2, pwm, speed, true);
		function -> drive_motor(4, 2, pwm, speed, true);
	}
	else if(direction == 4)
	{
		function -> drive_motor(1, 1, pwm, speed, true);
		function -> drive_motor(2, 2, pwm, speed, true);
		function -> drive_motor(3, 2, pwm, speed, true);
		function -> drive_motor(4, 1, pwm, speed, true);
	}
	else if(direction == 5)
	{
		function -> drive_motor(1, 1, pwm, speed, true);
		function -> drive_motor(2, 1, pwm, speed, true);
		function -> drive_motor(3, 1, pwm, speed, true);
		function -> drive_motor(4, 1, pwm, speed, true);
	}
	else if(direction == 6)
	{
		function -> drive_motor(1, 2, pwm, speed, true);
		function -> drive_motor(2, 2, pwm, speed, true);
		function -> drive_motor(3, 2, pwm, speed, true);
		function -> drive_motor(4, 2, pwm, speed, true);
	}
	delete function;
}

void Controller::NOP(void)
{
	this -> speed = 700;
	Function* function = new Function();
	function -> drive_motor(1, 3, 0, 0, false);
	function -> drive_motor(2, 3, 0, 0, false);
	function -> drive_motor(3, 3, 0, 0, false);
	function -> drive_motor(4, 3, 0, 0, false);
	delete function;
}

void Controller::X(void){}
void Controller::Y(void){}
void Controller::A(void){}
void Controller::B(void){}

void Controller::LB(void)
{
	Init_Move* init_move = new Init_Move();
	init_move -> init_move(E_robot_name::A);
	delete init_move;
}

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
	this -> footwork(1, speed);

	this -> direction = 1;
}

void Controller::CSR(void)
{
	this -> footwork(2, speed);

	this -> direction = 2;
}

void Controller::CSL(void)
{
	this -> footwork(4, speed);

	this -> direction = 4;
}

void Controller::CSD(void)
{
	this -> footwork(3, speed);

	this -> direction = 3;
}

void Controller::RSU(void)
{
	this -> speed += 50;
	if(this -> speed >= 1000)
	{
		this -> speed = 1000;
	}
	this -> footwork(this -> direction, this -> speed);
}

void Controller::RSR(void)
{
	this -> footwork(5, 400);

	this -> direction = 5;
}
void Controller::RSL(void)
{
	this -> footwork(6, 400);

	this -> direction = 6;
}
void Controller::RSD(void)
{
	this -> speed -= 50;
	if(this -> speed <= 300)
	{
		this -> speed = 300;
	}
	this -> footwork(this -> direction, this -> speed);

}


*/
