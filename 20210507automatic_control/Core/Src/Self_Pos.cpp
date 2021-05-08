/*
 * Self_Pos.cpp
 *
 *  Created on: 7 May 2021
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
#include "Self_Pos.hpp"

uint8_t Self_Pos::get_direction(void){
	return this -> direction;
}

void Self_Pos::Gyro(void){

}
uint32_t Self_Pos::encoder_read_5(void)
{
	return TIM5 -> CNT;
}
uint32_t Self_Pos::encoder_read_1(void)
{
	return TIM1 -> CNT;
}
uint32_t Self_Pos::encoder_read_3(void)
{
	return TIM3 -> CNT;
}


