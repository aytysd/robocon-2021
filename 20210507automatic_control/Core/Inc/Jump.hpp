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

	void jump( void );
	E_move_status get_status(void);
	void Jumping_PE_Sensor(void);
	void Jumping_Rope(void);
	static bool PE_1; //PC0
	static bool PE_2; //PC13
	static bool PE_3; //PA4
	static void get_Rope_Pos( uint8_t Rxdata );
private:

	static E_move_status status;
};



#endif /* INC_JUMP_HPP_ */
