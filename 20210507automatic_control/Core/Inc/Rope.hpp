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
	void stop_rope(uint8_t motor_number);
	void rotate_rope(uint8_t motor_number, uint8_t direction, uint16_t down_speed, uint16_t up_speed);

private:

	int encoder_read_4();
	int encoder_read_5();

};

#endif /* INC_ROPE_HPP_ */
