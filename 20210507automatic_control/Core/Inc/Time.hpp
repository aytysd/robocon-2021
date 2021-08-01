/*
 * Super_Wait.hpp
 *
 *  Created on: 29 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(provide super_class for wait class)
 *
 *@Attention_(please use this after inheriting )
 *
 *@Usertouch(functionname)&_(variable_name)
 *
 */
#ifndef INC_TIME_HPP_
#define INC_TIME_HPP_

#include "main.h"

enum class E_Time
{
	infinity = 45,
	double_jump = 30,

};


class Time
{
public:
	uint32_t calc_time_diff( void );
	void reset_timer( void );

private:
	static uint32_t prev_time;
};


#endif /* INC_TIME_HPP_ */
