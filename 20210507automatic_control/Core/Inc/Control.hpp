/*
 * Control.hpp
 *
 *  Created on: 9 Jul 2021
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
#ifndef INC_CONTROL_HPP_
#define INC_CONTROL_HPP_

#include "main.h"

class Control
{
public:
	static uint8_t master_Rxdata[4];
	static uint8_t A_Rxdata[4];
	static uint8_t B_Rxdata[4];

	void control(void);
};


#endif /* INC_CONTROL_HPP_ */
