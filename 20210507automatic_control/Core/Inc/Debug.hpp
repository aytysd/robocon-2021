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
#include <string>

using namespace std;

class Debug
{
public:
	template< typename addr >
	static void TTO_addr( addr var_addr, string str );
	template< typename type >
	static void TTO_val( type value, string str );

	static void time_calc( void );

private:

	void str_output( string str );

};


#endif /* INC_DEBUG_HPP_ */
