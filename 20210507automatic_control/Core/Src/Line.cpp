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
	a = -(tgY - befY);
	b = tgX - befX;
	c = -a*tgX - b*tgY;

	sqrtAABB = sqrt((long double)(a*a + b*b));

	r = atan((long double)(-b/a));

	tg_X = tgX;
	tg_Y = tgY;
}

double Line::distance(double x, double y)
{
	return ((a*x) + (b*y) + c) / sqrtAABB;
}

double Line::TGdistance(double x, double y)
{
	return ((-b*x) + (a*y) - (((-b)*tg_X) + (a*tg_Y))) / sqrtAABB;
}

int Line::MoveLine
(double befX, double befY, double tgX, double tgY,double x, double y, bool through)
{
	devX = this -> distance(x, y);
	devY = this -> TGdistance(x, y);

	devTG = sqrt((long double)(devX*devX + devY*devY));
	TG_r = atan((long double)((y - tg_Y)*(y -tg_Y) / (x - tg_X)*(x - tg_X)));
	TG_r = (TG_r * 180) / M_PI;

	this -> set(befX, befY, tgX, tgY);

	Self_Pos::Gyro* gyro = new Self_Pos::Gyro();
	now_r = (double)gyro -> get_direction();
	delete gyro;


	bool arrive = false;

	if(through == true)
	{
		if(devY <= 0)
		{
			arrive = true;
		}
	}
	else
	{
		bool inX = abs(tg_X - x) <= 100;
		bool inY = abs(tg_Y - y) <= 100;

		if(inX && inY)
		{
			arrive = true;
		}
		else
		{
			arrive = false;
		}
	}


	devTG *= 0.2;
	if(devTG > 2000)
	{
		devTG = 2000;
	}

	TG_r = TG_r - now_r;
	if(TG_r < 0)
	{
		TG_r = 360 + TG_r;
	}

	if(arrive == true)
	{
		if(through == true)
		{
			PWM* pwm = new PWM();

			TG_r = TG_r + 180;
			if(TG_r > 360)
			{
				TG_r = TG_r -360;
			}

			pwm -> V_output(100, TG_r, 0, now_r, E_move_status::MOVE);
			judge = 2;

			delete pwm;

		}
		else
		{
			PWM* pwm = new PWM();

			pwm -> V_output(devTG, TG_r, 0, now_r, E_move_status::STOP);
			judge = 1;

			delete pwm;
		}
	}
	else
	{
		PWM* pwm = new PWM();

		pwm -> V_output(devTG, TG_r, 0, now_r, E_move_status::MOVE);
		judge = 0;

		delete pwm;
	}

	return judge;
}




