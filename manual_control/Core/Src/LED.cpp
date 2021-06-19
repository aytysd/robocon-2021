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

E_LED_status LED::old_LED_status = E_LED_status::None;

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

		this -> old_LED_status = status;
		break;

	case E_LED_status::Done:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(3, 20);

		this -> old_LED_status = status;
		break;

	case E_LED_status::Wait:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(2, 20);

		this -> old_LED_status = status;
		break;

	case E_LED_status::Error_Handler:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(1, 20);
		break;

	case E_LED_status::OPR_Mode:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(2, 20);
		function -> drive_LED(3, 20);

		this -> old_LED_status = status;
		break;

	case E_LED_status::Warning:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(1, 20);
		function -> drive_LED(2, 20);
		break;

	case E_LED_status::Measurement:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		function -> drive_LED(1, 20);
		function -> drive_LED(3, 20);
		this -> old_LED_status = status;
		break;

	case E_LED_status::None:
		function -> drive_LED(1, 0);
		function -> drive_LED(2, 0);
		function -> drive_LED(3, 0);
		break;

	}

	delete function;

}

