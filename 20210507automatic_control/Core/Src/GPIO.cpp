/*
 * GPIO.cpp
 *
 *  Created on: May 22, 2021
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
#include <GPIO.hpp>
#include "main.h"

void GPIO::identify(uint16_t GPIO_Pin){
	switch(GPIO_Pin){
	case GPIO_PIN_0:
		this -> status[0] = true;
		break;
	case GPIO_PIN_1:
		this -> status[1] = true;
		break;
	case GPIO_PIN_2:
		this -> status[2] = true;
		break;
	case GPIO_PIN_3:
		this -> status[3] = true;
		break;
	case GPIO_PIN_4:
		this -> status[4] = true;
		break;

	case GPIO_PIN_5:
		this -> status[5] = true;
		break;
/*
	case GPIO_PIN_6:
		this -> status[6] = true;
		break;
	case GPIO_PIN_7:
		this -> status[7] = true;
		break;
	case GPIO_PIN_8:
		this -> status[8] = true;
		break;
	case GPIO_PIN_9:
		this -> status[9] = true;
		break;
	case GPIO_PIN_10:
		this -> status[10] = true;
		break;
*/
	case GPIO_PIN_11:
		this -> status[11] = true;
		break;
	case GPIO_PIN_12:
		this -> status[12] = true;
		break;
	case GPIO_PIN_13:
		this -> status[13] = true;
		break;
	case GPIO_PIN_14:
		this -> status[14] = true;
		break;
	case GPIO_PIN_15:
		this -> status[15] = true;
		break;

	}
}

bool GPIO::get_status(E_interrupt interrupt){
	for(int i = 0; i<15; i++){
		if( static_cast<int>(interrupt) == i ){

			bool temp = this -> GPIO::status[i];
			this -> GPIO::status[i] = false;
			return temp;
		}
	}
	return false;
}

bool GPIO::status[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
