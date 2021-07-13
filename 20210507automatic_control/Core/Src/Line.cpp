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
#include <stdio.h>
#include "Gyro.hpp"
#include "General_command.hpp"

int Line::AftX = 0;
int Line::AftY = 0;

int Line::BefX = 0;
int Line::BefY = 0;

E_Line_status Line::judge = E_Line_status::STOP;
bool Line::through = false;

void Line::set(int befX, int befY, int tgX, int tgY)
{
	this -> a = -(tgY - befY);
	this -> b = tgX - befX;
	this -> c = -a*tgX - b*tgY;

	this -> sqrtAABB = sqrt((long double)(a*a + b*b));
}

double Line::distance(int x, int y, int tgX, int tgY)
{
	if(sqrtAABB == 0)
	{
		sqrtAABB = 1;
	}
	return ((a*x) + (b*y) + c) / (int)sqrtAABB;
}

double Line::TGdistance(int x, int y, int tgX, int tgY)
{
	if(sqrtAABB == 0)
	{
		sqrtAABB = 1;
	}
	return ((-b*x) + (a*y) - (((-b)*tgX) + (a*tgY))) /(int) sqrtAABB;
}

void Line::MoveLine
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

	if((tgX == now_X) && (tgY > now_Y))
	{
		TG_r = 90;
	}
	else if((tgX == now_X) && (tgY < now_Y))
	{
		TG_r = 270;
	}
	else
	{
		if((tgX - this -> now_X) == 0)
		{
			tgX = 1;
		}
		this -> TG_r = atan(((long double)(tgY - this -> now_Y) / (long double)(tgX - this -> now_X)));
		this -> TG_r = ((long double)TG_r * (long double)180) / M_PI;
		if(tgX < this -> now_X)
		{
			TG_r = TG_r + 180;
		}
		else if(this -> TG_r < 0)
		{
			TG_r = TG_r + 360;
		}
		else if(this -> TG_r >= 360)
		{
			TG_r = TG_r - 360;
		}
	}

	Gyro* gyro = new Gyro();
	this -> now_r = (double)gyro -> get_direction( &hi2c1 );
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


	this -> TG_v = this -> devTG * 0.2;
	if(this -> TG_v > 1000)
	{
		this -> TG_v = 1000;
	}
  
	if(through == true)
	{
		if(this -> devTG > 1500)
		{
			this -> TG_v = 1000;
		}
		else if((this -> devTG > 1000) && (this -> devTG < 1500))
		{
			this -> TG_v = 750;
		}
		else if(this -> devTG < 1000)
		{
			this -> TG_v = 500;
		}
	}
  	char output[10];
	sprintf(output, "TG_v:%d\r\n", TG_v);
	HAL_UART_Transmit(&huart2, (uint8_t*)output, sizeof(output), 1000);

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

			pwm -> V_output(800, (uint16_t)this -> TG_r, 0, (uint16_t)this -> now_r, E_move_status::MOVE);
			judge = E_Line_status::THROUGHING;

			delete pwm;

		}
		else
		{
			PWM* pwm = new PWM();

			pwm -> V_output(this -> TG_v, (uint16_t)this -> TG_r, 0, (uint16_t)this -> now_r, E_move_status::STOP);
			judge = E_Line_status::STOP;

			delete pwm;
		}
	}
	else
	{
		PWM* pwm = new PWM();

		pwm -> V_output(this -> TG_v, (uint16_t)this -> TG_r, 0, (uint16_t)this -> now_r, E_move_status::MOVE);
		judge = E_Line_status::MOVING;

		delete pwm;
	}
}

void Line::Line_driver(int befX, int befY, int tgX, int tgY, bool through)
{
	this -> BefX = befX;
	this -> BefY = befY;
	this -> AftX = tgX;
	this -> AftY = tgY;
	this -> through = through;
}
