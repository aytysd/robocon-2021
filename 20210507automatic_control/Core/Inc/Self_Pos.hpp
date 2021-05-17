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



#include <General_command.hpp>
#include "main.h"

class Self_Pos{
public:
	int get_Self_Pos(void);
	int encoder_read_5(void);
	int encoder_read_2(void);
	Self_Pos(){
	}
	class Gyro{
	public:
		void BNO055_Init_I2C(I2C_HandleTypeDef* hi2c_device);
		void BNO055_update_gravity_direction(I2C_HandleTypeDef* hi2c_device);
		float get_gravity(void);
		int16_t get_direction(void);
		void set_initial_direction(E_robot_name robot);
	private:
		static float gravity;
		static int16_t direction;
		static int16_t initial_direction;

	};
private:
	static int Self_Pos;//(mm)
	static int encoder5;
	static int encoder2;


};



#endif /* INC_SELF_POS_HPP_ */


