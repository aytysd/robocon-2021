/*
 * LED.cpp
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

#include "LED.hpp"
#include "function.hpp"

void LED_Mode::LED_output(E_LED_status status)
{
	Function* function = new Function();


	switch(status)
	{
	case E_LED_status::Init:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(1, 20);
		function -> drive_LED(2, 20);
		function -> drive_LED(3, 20);

	case E_LED_status::Move:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(3, 20);


	case E_LED_status::Jump:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(2, 20);

	case E_LED_status::Stop:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(1, 20);

	case E_LED_status::Turn_the_rope:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(2, 20);
		function -> drive_LED(3, 20);

	case E_LED_status::Connecting:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(1, 20);
		function -> drive_LED(2, 20);

	case E_LED_status::Measurement:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(1, 20);
		function -> drive_LED(3, 20);
	}

	delete function;
}

