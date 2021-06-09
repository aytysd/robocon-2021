/*
 * Communication.hpp
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
#ifndef INC_COMMUNICATION_HPP_
#define INC_COMMUNICATION_HPP_

#include "main.h"

enum class E_data_type
{
	CURRENT_DATA,
	ERROR_DATA,
	WARNING_DATA,
	COUNT,
};


class Communication
{
public:
	static uint8_t Rxdata[4];
	void send_data(E_data_type data);
private:

};



#endif /* INC_COMMUNICATION_HPP_ */
