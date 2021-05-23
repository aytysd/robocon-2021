/*
 * LED.hpp
 *
 *  Created on: 14 May 2021
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
#ifndef INC_LED_HPP_
#define INC_LED_HPP_

enum class E_LED_status
{
	Init,
	Move,
	Stop,
	Jump,
	Turn_the_rope,
	Connecting,
	Measurement,
};

class LED_Mode
{
public:
	void LED_output(E_LED_status status);
};



#endif /* INC_LED_HPP_ */
