/*
 * Self_Pos.hpp
 *
 *  Created on: 7 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(get self position, direction)
 *
 *@Input(address of hi2c(e.g. &hi2c1))in(I2C_HandleTypeDef* hi2c_device)of(void BNO055_Init_I2C)
 *@Input(address of hi2c(e.g. &hi2c1))in(I2C_HandleTypeDef* hi2c_device)of(void BNO055_update_gravity_direction)
 *@Input(robot name in enum_class E_robot_name)in(E_robot_name)of(void set_initial_direction())
 *@Input(value)in(variable)of(functionname)
 *@Input(value)in(variable)of(functionname)
 *
 *@Output(gravity value(usually 9.8))to(float gravity)
 *@Output(direction value(0 to 360))to(int16_t direction)
 *
 *@Attention_(you have to use Gyro::BNO_Init_I2C function in main function before diving into while(1){}.)
 *@Attention_(you have to initialise before using void get_direction())
 *
 *@Usertouch(Gyro::BNO_Init_I2C())
 *@Usertouch(Gyro::BNO_update_gravity())
 *@Usertouch(Gyro::get_gravity())
 *@Usertouch(Gyro::get_direction())
 *@Usertouch(Gyro::set_direction(E_robot_name robot))
 *
 */
#ifndef INC_SELF_POS_HPP_
#define INC_SELF_POS_HPP_

#define OD_RADIUS 25.4
#define DT 0.1

#include <General_command.hpp>
#include "main.h"
#include "ToF.hpp"

class Self_Pos
{
public:
	void set_initial_pos(E_robot_name robot);
	void update_self_pos(void);

	int get_Self_Pos_X(void);
	int get_Self_Pos_Y(void);

	void add_Self_Pos( int add_x, int add_y );

	int Self_Pos_config(void);


	int encoder_read_5(void);
	int encoder_read_2(void);


	void update_self_pos_ToF();

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
private:

	int calc_diff( int prev_x, int prev_y, int current_x, int current_y );

	static int Self_Pos_X;
	static int Self_Pos_Y;


};



#endif /* INC_SELF_POS_HPP_ */


