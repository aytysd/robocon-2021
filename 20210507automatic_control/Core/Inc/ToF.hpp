/*
 * ToF.hpp
 *
 *  Created on: 19 May 2021
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
#ifndef INC_TOF_HPP_
#define INC_TOF_HPP_

#include "main.h"
#define TOF_ADDRESS 0x52

class ToF{
public:
	uint16_t get_distance(void);
	void update_distance(void);
	void init_ToF(void);
private:
	static uint16_t distance;
};


#endif /* INC_TOF_HPP_ */
