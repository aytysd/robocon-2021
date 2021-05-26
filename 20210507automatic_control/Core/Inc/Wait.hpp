/*
 * Wait.hpp
 *
 *  Created on: 27 May 2021
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
#ifndef SRC_WAIT_HPP_
#define SRC_WAIT_HPP_


class Wait{
protected:
	bool status_1;
	bool status_2;
	bool status_3;
public:
	bool wait(bool condition);

};


#endif /* SRC_WAIT_HPP_ */
