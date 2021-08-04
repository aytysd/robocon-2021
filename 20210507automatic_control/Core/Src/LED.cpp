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


void LED::LED_output(E_LED_status status)
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

		break;

	case E_LED_status::Done:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(3, 20);

		break;

	case E_LED_status::NONE:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(2, 20);

		break;

	case E_LED_status::MOVE_INFINITY_INITIAL_POS:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(1, 20);
		break;

	case E_LED_status::SPC:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(2, 20);
		function -> drive_LED(3, 20);

		break;

	case E_LED_status::MOVE_DOUBLE_JUMP_INITIAL_POS:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(1, 20);
		function -> drive_LED(2, 20);
		break;

	case E_LED_status::MODE_INFINITY_JUMP:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(1, 20);
		function -> drive_LED(3, 20);
		break;

	case E_LED_status::MODE_DOUBLE_JUMP:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		break;

	}

	delete function;

}

