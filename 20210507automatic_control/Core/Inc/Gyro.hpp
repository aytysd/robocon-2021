/*
 * Gyro.hpp
 *
 *  Created on: 12 Jul 2021
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
#ifndef INC_GYRO_HPP_
#define INC_GYRO_HPP_

#include "main.h"
#include "General_command.hpp"


class Gyro
{
public:
	void BNO055_Init_I2C(I2C_HandleTypeDef* hi2c_device);
	void BNO055_update_gravity_direction(I2C_HandleTypeDef* hi2c_device);
	float get_gravity(void);
	uint16_t get_direction(void);
	void set_initial_direction(E_robot_name robot);
private:
	static float gravity;
	static uint16_t direction;
	static uint16_t initial_direction;

};


#endif /* INC_GYRO_HPP_ */
