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

class Debug
{
public:
	template< typename addr >
	static void TTO( addr var_addr, const char* str );
	static void time_calc();

};


#endif /* INC_DEBUG_HPP_ */
