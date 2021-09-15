/*
 * Control_C.hpp
 *
 *  Created on: Sep 14, 2021
 *      Author: aytys
 */

#ifndef INC_CONTROL_C_HPP_
#define INC_CONTROL_C_HPP_


class Control_C
{

public:

	static bool A_ready_flag;
	static bool B_ready_flag;

	void control_C( void );
	void wait_for_ab( void );


private:

	void stay_jump( void );
	void cross_jump( void );
	void infinity_jump( void );

	void send_both( uint8_t* data );

};


#endif /* INC_CONTROL_C_HPP_ */
