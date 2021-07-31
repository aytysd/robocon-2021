/*
 * Time.cpp
 *
 *  Created on: 13 Jul 2021
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

#include "Time.hpp"
#include "stdio.h"
#include "main.h"


uint32_t Time::prev_time = 0;

void Time::reset_timer( void ){ Time::prev_time = HAL_GetTick(); }

uint32_t Time::calc_time_diff( void )
{
	uint32_t diff = HAL_GetTick() - Time::prev_time;
	return diff / 1000;
}
