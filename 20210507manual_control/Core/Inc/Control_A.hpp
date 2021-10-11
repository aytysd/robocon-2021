/*
 * Control_A.hpp
 *
 *  Created on: Sep 14, 2021
 *      Author: aytys
 */

#ifndef INC_CONTROL_A_HPP_
#define INC_CONTROL_A_HPP_


class Control_A
{
public:
	void control_A( void );

	static bool start_flag;

	static bool B_ready_flag;

private:

	void stay_jump( void );
	void cross_jump( void );
	void infinity_jump( void );

};


#endif /* INC_CONTROL_A_HPP_ */
