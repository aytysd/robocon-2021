/*
 * GPIO.hpp
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
#ifndef INC_GPIO_HPP_
#define INC_GPIO_HPP_

#include "main.h"

enum class E_which{
	PE_SENSOR =0,
	UNDER_SW_V4,
	LIMIT_F_V3,
	LIMIT_L_V3,
	SPARE1,
	LIMIT_F_V2,
	SPARE2,
	SPARE3,
	SPARE4,
	SPARE5,
	SPARE6,
	UNDER_SW_V3,
	UNDER_SW_V2,
	LIMIT_L_V4,
	UNDER_SW_V1,
	SPARE7,


};

class GPIO{
public:
	void identify(uint16_t GPIO_Pin);
	bool get_status(E_which which);
private:
	static bool status[16];

};


#endif /* INC_GPIO_HPP_ */
