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
 *@Input(address of hi2c(e.g. &hi2c1))in(I2C_HandleTypeDef* hi2c_device)of(BNO055_update_gravity_direction)
 *@Input(value)in(variable)of(functionname)
 *@Input(value)in(variable)of(functionname)
 *
 *@Output(gravity value(usually 9.8))to(float gravity)
 *@Output(direction value(0 to 360))to(int16_t direction)
 *
 *@Attention_(you have to use Gyro::BNO_Init_I2C function in main function before diving into while(1){}.)
 *@Attention_()
 *
 *@Usertouch(Gyro::BNO_Init_I2C)
 *@Usertouch(Gyro::BNO_update_gravity)
 *@Usertouch(Gyro::get_gravity)
 *@Usertouch(Gyro::get_direction)
 *
 */
#ifndef INC_SELF_POS_HPP_
#define INC_SELF_POS_HPP_



#include "main.h"

class Self_Pos{
public:
	Self_Pos(){
		this -> direction = 0;
	}
	uint8_t get_direction();
	class Gyro{
	public:
		void BNO055_Init_I2C(I2C_HandleTypeDef* hi2c_device);
		void BNO055_update_gravity_direction(I2C_HandleTypeDef* hi2c_device);
		float get_gravity(void);
		int16_t get_direction(void);
	private:
		float gravity;
		int16_t direction;

	};
private:
	uint8_t direction;
	uint32_t encoder_read_5(void);
	uint32_t encoder_read_3(void);
	uint32_t encoder_read_1(void);

};



#endif /* INC_SELF_POS_HPP_ */
