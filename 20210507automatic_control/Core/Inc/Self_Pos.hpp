/*
 * Self_Pos.hpp
 *
 *  Created on: 7 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(get self position, direction)
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
#ifndef INC_SELF_POS_HPP_
#define INC_SELF_POS_HPP_

#define	IMU_NUMBER_OF_BYTES					18

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
		uint8_t GetAccelData(I2C_HandleTypeDef* hi2c_device, uint8_t* str);
	private:

	};
private:
	uint8_t direction;
	uint32_t encoder_read_5(void);
	uint32_t encoder_read_3(void);
	uint32_t encoder_read_1(void);

};



#endif /* INC_SELF_POS_HPP_ */
