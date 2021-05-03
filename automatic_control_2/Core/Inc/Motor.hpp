/*
 * pwm.hpp
 *
 *  Created on: May 3, 2021
 *      Author: Ayato Yoshida
 */

#ifndef INC_MOTOR_HPP_
#define INC_MOTOR_HPP_

#include "main.h"

class Motor{
public:
	void V_output(double V, double fai, double rotation_speed, double attitude_angle);
	void drive_motor(int motor_number, int direction, int PWM);

	void get_V_output();

};


#endif /* INC_MOTOR_HPP_ */
