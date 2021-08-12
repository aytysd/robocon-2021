/*
 * Rope.hpp
 *
 *  Created on: 8 Jul 2021
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
#ifndef INC_ROPE_HPP_
#define INC_ROPE_HPP_

class Rope
{
public:
	static int over_flow_cnt_3;
	static int over_flow_cnt_4;
	static int over_flow_cnt_5;

	int encoder_read_3();

private:

	int encoder_read_4();
	int encoder_read_5();

	void stop_rope();
	void rotate_rope();

};



#endif /* INC_ROPE_HPP_ */
