/*
 * Jump.hpp
 *
 *  Created on: 9 May 2021
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
#ifndef INC_JUMP_HPP_
#define INC_JUMP_HPP_

#include "General_command.hpp"
#include "main.h"

class Jump
{
public:

	void identify(void);
	E_move_status get_status(void);
	void Jumping_PE_Sencor(void);
	void Jumping_Rope(void);
private:

	void pre_calc(void);
	void calc_fly_distance(void);
	uint16_t jump_speed = 0;
	double x_y_prop = 0;

	static E_move_status status;

};



#endif /* INC_JUMP_HPP_ */
