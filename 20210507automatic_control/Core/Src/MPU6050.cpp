/*
 * mpu6050.c
 *
 *  Created on: Nov 13, 2019
 *      Author: Bulanov Konstantin
 *
 *  Contact information
 *  -------------------
 *
 * e-mail   :  leech001@gmail.com
 */



#include <math.h>
#include <MPU6050.hpp>
#include "General_command.hpp"
#include "Debug.hpp"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


double MPU6050::robot_direction = 0;
uint16_t MPU6050::robot_initial_direction = 0;
double MPU6050::table_direction = 0;


bool MPU6050::MPU6050_Init(I2C_HandleTypeDef *I2Cx)
{
    uint8_t check;
    uint8_t Data;

    // check device ID WHO_AM_I

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, i2c_timeout);

    if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
    {
        // power management register 0X6B we should write all 0's to wake the sensor up
        Data = 0;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, i2c_timeout);

        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
        Data = 0x07;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, i2c_timeout);

        // Set accelerometer configuration in ACCEL_CONFIG Register
        // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
        Data = 0x00;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, i2c_timeout);

        // Set Gyroscopic configuration in GYRO_CONFIG Register
        // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
        Data = 0x18;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, i2c_timeout);
        return false;
    }
    return true;
}



void MPU6050::MPU6050_update_Gyro(I2C_HandleTypeDef *I2Cx )
{
    uint8_t Rec_Data[6];
    int16_t Gyro_Z_RAW = 0;
    double buff = 0;
    // Read 6 BYTES of data starting from GYRO_XOUT_H register

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, i2c_timeout);

    Gyro_Z_RAW = (int16_t) (Rec_Data[4] << 8 | Rec_Data[5]);
    /*** convert the RAW values into dps (�/s)
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 131.0
         for more details check GYRO_CONFIG Register              ****/

    if( I2Cx == &hi2c1 )
    {
        buff = Gyro_Z_RAW - 2.7915;
        this -> robot_direction += IT_PERIOD * buff / 16.4;
//        Debug::TTO_val( ( uint16_t )this -> robot_direction, "gyro:", &huart2 );

    }
    else if( I2Cx == &hi2c3 )
    {
        buff = Gyro_Z_RAW - 2.7915;
        this -> table_direction += IT_PERIOD * buff / 16.4;

    }

//    Debug::TTO_val( this -> robot_direction, "Gyro", &huart2 );
}

double MPU6050::get_direction( I2C_HandleTypeDef *I2Cx )
{
	if( I2Cx == &hi2c1 )
	{
		while( this -> robot_direction > 360 )
			this -> robot_direction -= 360;
		while( this -> robot_direction < 0 )
			this -> robot_direction += 360;

		return this -> robot_direction;
	}
	else if( I2Cx == &hi2c3 )
	{
		while( this -> table_direction > 360 )
			this -> table_direction -= 360;
		while( this -> table_direction < 0 )
			this -> table_direction += 360;

		return this -> table_direction;

	}
}

void MPU6050::set_initial_direction(E_robot_name robot)
{
	switch(robot)
	{
	case E_robot_name::A:
		this -> robot_initial_direction = 0;
		break;
	case E_robot_name::B:
		this -> robot_initial_direction = 90;
		break;
	case E_robot_name::C:
		this -> robot_initial_direction = 180;
		break;
	default:
		break;
	}
}



