/*
 * PWM.hpp
 *
 *  Created on: May 4, 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Description_method:V_output :determine V1, V2, V3, V4 PWM from direction, speed, rotation speed, attitutde angle
 *
 *@Input_( the speed of machine (mm/s) ) in ( double V ) of ( PWM::V_output )
 *@Input_( direction ( from 0 to 360 ) ) in ( double fai ) of ( PWM::V_output )
 *@Input_( speed when it rotates ( mm/s ) )_in ( double rotation_speed ) of ( PWM::V_output )
 *@Input_( which direction the robot directs. Get this value from Gyro sensor ( from 0 to 360 ))_in_( double attitude_angle )_of_( PWM::V_output )
 *@Input_( stop, free, or move ( stop == E_move_status::STOP, free == E_move_status::FREE, move == E_move_status::MOVE) in ( E_move_status status ) of ( PWM::V_output )
 *
 *@Output ( the result of PWM, direction, motor number)_to_( each MD )
 *
 *@Attention
 *
 */

#ifndef INC_PWM_HPP_
#define INC_PWM_HPP_

#include "main.h"
#include "General_command.hpp"

class PWM{
public:
	void V_output(double V, double fai, double rotation_speed, double attitude_angle, E_move_status status);
private:
	uint8_t plus_minus(double number);

};



#endif /* INC_PWM_HPP_ */
