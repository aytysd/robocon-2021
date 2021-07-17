/*
 * Debug.hpp
 *
 *  Created on: 17 Jul 2021
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
#ifndef INC_DEBUG_HPP_
#define INC_DEBUG_HPP_

#include "main.h"

class Debug
{
public:
	template< typename addr >
	static void TTO( addr var_addr, const char* str, UART_HandleTypeDef* UART );
	static void time_calc( UART_HandleTypeDef* UART );

};


#endif /* INC_DEBUG_HPP_ */
