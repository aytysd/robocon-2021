/*
 * Self_Pos.hpp
 *
 *  Created on: 7 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(get self position, direction)
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
#ifndef INC_SELF_POS_HPP_
#define INC_SELF_POS_HPP_


#include "main.h"

class Self_Pos{
public:
	Self_Pos(){
		this -> direction = 0;
	}
	uint8_t get_direction();
	void Gyro(void);
private:
	uint8_t direction;

};



#endif /* INC_SELF_POS_HPP_ */
