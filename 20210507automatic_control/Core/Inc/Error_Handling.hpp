/*
 * Error_Handler.hpp
 *
 *  Created on: Jun 5, 2021
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
#ifndef INC_ERROR_HANDLING_HPP_
#define INC_ERROR_HANDLING_HPP_

#include "main.h"

enum class E_Errors
{
	Init_move_failed,
	Initialization_failed,
	Encoder_Disconnection,
	Count,
};

class Error_Handling
{
public:
	void Emergency_stop(void);
	void set_flag(E_Errors errors);


	static const char* error_func;
	static uint32_t error_line;
private:
	static bool flag[static_cast<int>(E_Errors::Count) + 1 ];
};





#endif /* INC_ERROR_HANDLING_HPP_ */
