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
#ifndef INC_GPIO5_9_HPP_
#define INC_GPIO5_9_HPP_


class GPIO5_9{
public:
	void identify(void);
private:
	static bool status[5] = {false, false, false, false, false};

};


#endif /* INC_GPIO5_9_HPP_ */
