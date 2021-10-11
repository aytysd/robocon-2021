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

//#define PE_Jump 1
//#define PE_Self_Pos 2
class Jump
{
public:

	void jump( void );
	void Jump_driver( E_Jump_status status );
	E_Jump_status get_Jump_status(void);

	static E_Jump_status Jump_status;



};



#endif /* INC_JUMP_HPP_ */
