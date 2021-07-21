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

int Rope::over_flow_cnt_3 = -1;
int Rope::over_flow_cnt_4 = -1;
int Rope::over_flow_cnt_5 = -1;

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
