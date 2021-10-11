/*
 * Follow.hpp
 *
 *  Created on: 4 Aug 2021
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
#ifndef INC_FOLLOW_HPP_
#define INC_FOLLOW_HPP_

#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#define FOLLOW_RADIUS 50

class Follow
{
public:
	static int16_t A_pos_x;
	static int16_t A_pos_y;

	void follow( void );

private:

	static int target_X;
	static int target_Y;

	void target_calc( void );

};



#endif /* INC_FOLLOW_HPP_ */
