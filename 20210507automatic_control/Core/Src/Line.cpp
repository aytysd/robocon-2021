/*
 * Line.hpp
 *
 *  Created on: 2021/05/08
 *
 *@Author: nakakubo hiroto
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
#include "Line.hpp"
#include "math.h"
#include "PWM.hpp"
#include "Self_Pos.hpp"

void Line::set(double befX, double befY, double tgX, double tgY)
{
	this -> a = -(tgY - befY);
	this -> b = tgX - befX;
	this -> c = -a*tgX - b*tgY;

	this -> sqrtAABB = sqrt((long double)(a*a + b*b));
}

double Line::distance(double x, double y, double tgX, double tgY)
{
	return ((a*x) + (b*y) + c) / sqrtAABB;
}

double Line::TGdistance(double x, double y, double tgX, double tgY)
{
	return ((-b*x) + (a*y) - (((-b)*tgX) + (a*tgY))) / sqrtAABB;
}

int Line::MoveLine
(double befX, double befY, double tgX, double tgY, bool through)
{
	this -> set(befX, befY, tgX, tgY);

	Self_Pos* self_pos = new Self_Pos();
	this -> now_X = self_pos -> get_Self_Pos_X();
	this -> now_Y = self_pos -> get_Self_Pos_Y();
	delete self_pos;

	this -> devX = this -> distance(this -> now_X, this -> now_Y, tgX, tgY);
	this -> devY = this -> TGdistance(this -> now_X, this -> now_Y, tgX, tgY);

	this -> devTG = sqrt((long double)(this -> devX*this -> devX + this -> devY*this -> devY));
	this -> TG_r = atan((long double)((this -> now_Y - tgY) / (this -> now_X - tgX)));
	this -> TG_r = (TG_r * 180) / M_PI;

	Self_Pos::Gyro* gyro = new Self_Pos::Gyro();
	this -> now_r = (double)gyro -> get_direction();
	delete gyro;


	bool arrive = false;

	if(through == true)
	{
		if(this -> devY <= 0)
		{
			arrive = true;
		}
	}
	else
	{
		bool inX = abs(tgX - now_X) <= 100;
		bool inY = abs(tgY - now_Y) <= 100;

		if(inX && inY)
		{
			arrive = true;
		}
		else
		{
			arrive = false;
		}
	}


	this -> devTG *= 0.2;
	if(this -> devTG > 2000)
	{
		this -> devTG = 2000;
	}

	this -> TG_r = this -> TG_r - this -> now_r;
	if(this -> TG_r < 0)
	{
		this -> TG_r = 360 + this -> TG_r;
	}

	if(arrive == true)
	{
		if(through == true)
		{
			PWM* pwm = new PWM();

			this -> TG_r = this -> TG_r + 180;
			if(this -> TG_r > 360)
			{
				this -> TG_r = this -> TG_r -360;
			}

			pwm -> V_output(100, this -> TG_r, 0, now_r, E_move_status::MOVE);
			judge = 2;

			delete pwm;

		}
		else
		{
			PWM* pwm = new PWM();

			pwm -> V_output(this -> devTG, this -> TG_r, 0, this -> now_r, E_move_status::STOP);
			judge = 1;

			delete pwm;
		}
	}
	else
	{
		PWM* pwm = new PWM();

		pwm -> V_output(this -> devTG, this -> TG_r, 0, this -> now_r, E_move_status::MOVE);
		judge = 0;

		delete pwm;
	}

	return judge;
}




