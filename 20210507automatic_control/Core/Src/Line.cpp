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
#include "Gyro.hpp"

void Line::set(int befX, int befY, int tgX, int tgY)
{
	this -> a = -(tgY - befY);
	this -> b = tgX - befX;
	this -> c = -a*tgX - b*tgY;

	this -> sqrtAABB = sqrt((long double)(a*a + b*b));
}

double Line::distance(int x, int y, int tgX, int tgY)
{
	return ((a*x) + (b*y) + c) / (int)sqrtAABB;
}

double Line::TGdistance(int x, int y, int tgX, int tgY)
{
	return ((-b*x) + (a*y) - (((-b)*tgX) + (a*tgY))) /(int) sqrtAABB;
}

int Line::MoveLine
(int befX, int befY, int tgX, int tgY, bool through)
{
	this -> set(befX, befY, tgX, tgY);

	Self_Pos* self_pos = new Self_Pos();
	this -> now_X = self_pos -> get_Self_Pos_X();
	this -> now_Y = self_pos -> get_Self_Pos_Y();
	delete self_pos;

	this -> devX = this -> distance(this -> now_X, this -> now_Y, tgX, tgY);
	this -> devY = this -> TGdistance(this -> now_X, this -> now_Y, tgX, tgY);
	this -> devX = fabs(devX);
	this -> devY = fabs(devY);

	this -> devTG = sqrt((long double)(this -> devX*this -> devX + this -> devY*this -> devY));
	this -> TG_r = atan((long double)((this -> now_Y - tgY) / (this -> now_X - tgX)));
	this -> TG_r = ((uint16_t)TG_r * 180) / M_PI;

	Gyro* gyro = new Gyro();
	this -> now_r = (double)gyro -> get_direction();
	delete gyro;


	bool arrive = false;

	if(through == true)
	{
		if(this -> devY <= 500)
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
	if(this -> devTG > 1000)
	{
		this -> devTG = 1000;
	}

	this -> TG_r = (uint16_t)this -> TG_r - this -> now_r;
	if(this -> TG_r < 0)
	{
		this -> TG_r = 360 + (uint16_t)this -> TG_r;
	}

	if(through == true)
	{
		devTG = 800;
	}

	if(arrive == true)
	{
		if(through == true)
		{
			PWM* pwm = new PWM();

//			this -> TG_r = this -> TG_r + 180;
//			if(this -> TG_r > 360)
//			{
//				this -> TG_r = this -> TG_r -360;
//			}

			pwm -> V_output(800, (double)this -> TG_r, 0, (double)this -> now_r, E_move_status::MOVE);
			judge = 2;

			delete pwm;

		}
		else
		{
			PWM* pwm = new PWM();

			pwm -> V_output((double)this -> devTG, (double)this -> TG_r, 0, (double)this -> now_r, E_move_status::STOP);
			judge = 1;

			delete pwm;
		}
	}
	else
	{
		PWM* pwm = new PWM();

		pwm -> V_output((double)this -> devTG, (double)this -> TG_r, 0, (double)this -> now_r, E_move_status::MOVE);
		judge = 0;

		delete pwm;
	}

	return judge;
}
