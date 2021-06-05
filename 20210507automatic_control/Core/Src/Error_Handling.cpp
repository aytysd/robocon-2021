/*
 * Error_Handler.cpp
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

#include <Error_Handling.hpp>
#include "main.h"
#include "Function.hpp"

void Error_Handling::Emergency_stop()
{
	Function* function = new Function();
	for(int i = 0; i<8; i++){

		function -> drive_motor(i, 0, 0, 0, false);
	}

}

void Error_Handling::set_flag(E_Errors errors)
{
	for( int i = 0; i<static_cast<int>(E_Errors::Count); i++)
	{
		if( static_cast<int>(errors) == i )
		{
			this -> flag[i] = true;
		}
	}

}


const char* Error_Handling::error_func = 0;
uint32_t Error_Handling::error_line = 0;

bool Error_Handling::flag[ static_cast<int>(E_Errors::Count) + 1 ] = { false, false, false, false };
