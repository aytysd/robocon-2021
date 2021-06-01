/*
 * GPIO.hpp
 *
 *  Created on: May 22, 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(identify which interrupt happened)
 *
 *@Input(interrupt label which you want to observe, listed in enum class E_interrupt)in(E_interrupt interrupt)of(bool get_status())
 *
 *@Output(true or false)to(get_status())
 *
 *@Attention_(once you get specific status via get_status(), the value of bool status[16] that you get will automatically be changed to false)
 *
 *@Usertouch(bool get_status())
 *
 */
#ifndef INC_GPIO_HPP_
#define INC_GPIO_HPP_

#include "main.h"

enum class E_interrupt{
	PE_SENSOR_T =0,
	UNDER_SW_V4,
	LIMIT_F_V3,
	LIMIT_L_V3,
	PE_SENSOR_F,
	LIMIT_F_V2,
	SPARE2,//cannot be used
	SPARE3,//cannot be used
	LIMIT_L_V4,
	SPARE5,//cannot be used
	SPARE6,//cannot be used
	UNDER_SW_V3,
	UNDER_SW_V2,
	PE_SENSOR_B,
	UNDER_SW_V1,
	SPARE7,


};

class GPIO{
public:
	void identify(uint16_t GPIO_Pin);
	bool get_status(E_interrupt interrupt);
	void reset_status();

private:
	static bool status[16];

};


#endif /* INC_GPIO_HPP_ */
