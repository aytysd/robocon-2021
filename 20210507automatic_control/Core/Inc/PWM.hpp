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

#define PPR 2048
#define DT 0.1

#define CW 1
#define CCW 2
#define BRAKE 3

#define dis_diff_Kp 0.5
#define dis_diff_Kd 0.1

#define ang_diff_Kp 2
#define ang_diff_Kd 0.1

class PWM
{
public:
	void V_output(uint16_t V, uint16_t fai, int16_t rotation_speed, uint16_t attitude_angle, E_move_status status);
	void Front_Move( uint16_t V, uint16_t fai, uint16_t attitude_angle, double Line_dis_diff, E_move_status status);
	bool rotate(uint16_t V, uint16_t target_angle);

private:
	uint8_t plus_minus(double number);

	static int16_t pre_dis_diff;
	static int16_t pre_ang_diff;

};



#endif /* INC_PWM_HPP_ */
