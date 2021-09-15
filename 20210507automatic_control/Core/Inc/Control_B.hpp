/*
 * Control_B.hpp
 *
 *  Created on: Sep 14, 2021
 *      Author: aytys
 */

#ifndef INC_CONTROL_B_HPP_
#define INC_CONTROL_B_HPP_

class Control_B
{
public:

	void control_B( void );

	static bool start_flag;
private:

	void stay_jump( void );
	void cross_jump( void );
	void infinity_jump( void );


};



#endif /* INC_CONTROL_B_HPP_ */
