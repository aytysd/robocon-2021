/*
 * Calc.hpp
 *
 *  Created on: May 3, 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Description_method:plus_minus: this function is for Motor::drive_motor. decide whether the argument is positive, negative, or 0, and return 1, 2, or 3 ( CW, CCW , BRAKE ).
 *
 *@Input_value: double number : the number to judge whether negative, positive, or 0
 *
 *@Input_where:the argument of Calc::plus_minus
 *
 *@Output_value: if the argument == negative -> 2 ( CCW )
 *@Output_value: if the argument == positive -> 1 ( CW )
 *@Output_value: if the argument == 0 -> ( BRAKE )
 *
 *@Output where: return sentence
 *
 *@Attention
 *
 */

#ifndef INC_CALC_HPP_
#define INC_CALC_HPP_


class Calc{
public:
	int plus_minus(double number);
};


#endif /* INC_CALC_HPP_ */
