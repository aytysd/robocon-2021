/*
 * Rope.cpp
 *
 *  Created on: 8 Jul 2021
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

#include "main.h"
#include "Rope.hpp"
#include "Debug.hpp"
#include "Function.hpp"
#include "PWM.hpp"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


int Rope::over_flow_cnt_3 = -1;
int Rope::over_flow_cnt_4 = -1;
int Rope::over_flow_cnt_5 = -1;

bool run = false;
bool force_stop = false;
int last_encoder_pos = 0;

int Rope::encoder_read_3()
{
	int enc_buff = this -> over_flow_cnt_3 * 0x10000 + TIM3 -> CNT;
	return enc_buff;
}

int Rope::encoder_read_4()
{
	int enc_buff = this -> over_flow_cnt_4 * 0x10000 + TIM4 -> CNT;
	return enc_buff;
}

int Rope::encoder_read_5()
{
	int enc_buff = TIM5 -> CNT % 2048;
	return enc_buff;
}

//rotate_rope(5, CW, 1040, 520);
void rotate_rope(uint8_t motor_number, uint8_t direction, uint16_t down_speed, uint16_t up_speed)
{
	if( run == true ) return;

	Function* function = new Function();
	Rope* rope = new Rope();

	if( run == false && rope -> encoder_read_3() != last_encoder_pos ) run = true;

	while( run == true )
	{
		if( rope -> encoder_read_3() > 1024 )
		{
			function -> drive_motor_Rope(motor_number, direction, up_speed, false);

			for(int i=0;i<100;++i)
			{
				HAL_Delay(1);
				if( force_stop == true ) return;
			}
		}
		else
		{
			function -> drive_motor_Rope(motor_number, direction, down_speed, false);

			for(int i = 0; i < 100; ++i)
			{
				HAL_Delay(1);
				if( force_stop == true ) return;
			}
		}
	}

	delete function;
	delete rope;
}

//stop_rotate(5);
void stop_rope(uint8_t motor_number)
{
	Function* function = new Function();
	Rope* rope = new Rope();

	run = false;
	force_stop = true;
	function -> drive_motor_Rope(motor_number, BRAKE, 0, true);
	last_encoder_pos = rope -> encoder_read_3();

	delete function;
	delete rope;
}
