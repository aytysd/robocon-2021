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


double MPU6050::robot_direction = 1.03;
uint16_t MPU6050::robot_initial_direction = 0;
double MPU6050::table_direction = 0;

bool MPU6050::sampling = false;
bool MPU6050::testing = false;

double gy_data = 0;

bool MPU6050::MPU6050_Init( void )
{
    uint8_t check;
    uint8_t Data;

    // check device ID WHO_AM_I

    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, i2c_timeout);

    if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
    {
        // power management register 0X6B we should write all 0's to wake the sensor up
        Data = 0;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, i2c_timeout);

        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
        Data = 0x07;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, i2c_timeout);

        // Set accelerometer configuration in ACCEL_CONFIG Register
        // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
        Data = 0x00;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, i2c_timeout);

        // Set Gyroscopic configuration in GYRO_CONFIG Register
        // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
        Data = 0x18;
        HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, i2c_timeout);


		uint32_t start_time_1 = HAL_GetTick();
		MPU6050::sampling = true;
		HAL_TIM_Base_Start_IT( &htim6 );
		while( ( ( HAL_GetTick() / 1000 ) - ( start_time_1 / 1000 ) ) < SAMPLING_PERIOD ){}
		MPU6050::sampling = false;

		uint32_t start_time_2 = HAL_GetTick();
		MPU6050::testing = true;
		while( ( ( HAL_GetTick() / 1000 ) - ( start_time_2 / 1000 ) ) < TESTING_PERIOD ){}
		MPU6050::testing = false;


        return false;
    }
    return true;
}



void MPU6050::MPU6050_update_Gyro( void )
{
    uint8_t Rec_Data[6];
    int16_t Gyro_Z_RAW = 0;

    static double med_1;
    static double buff_1[ 150 ];

    static double med_3;
    static double buff_3[ 150 ];

    static uint32_t count_1;
    static double diff_per_IT_1;

    static uint32_t count_3;
    static double diff_per_IT_3;


    static bool diff_calc_1 = true;
    static bool diff_calc_3 = true;


    HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, i2c_timeout);

    Gyro_Z_RAW = (int16_t) ( Rec_Data[4] << 8 | Rec_Data[5] );

	if( MPU6050::sampling == true )
	{
		buff_1[ count_1 ] = Gyro_Z_RAW / 16.4;
		count_1++;
		return;
	}
	else if( MPU6050::testing == true )
	{
		this -> sort_data( buff_1, 50 );
		med_1 = ( buff_1[ 24 ] + buff_1[ 25 ] ) / 2;

		this -> robot_direction += IT_PERIOD * ( ( Gyro_Z_RAW / 16.4 ) + ( -1 * med_1 ) );

	}
	else
	{
		if( diff_calc_1 == true )
		{
			diff_per_IT_1 = ( this -> robot_direction / SAMPLING_PERIOD ) * 0.1;
			this -> robot_direction = 0;
			diff_calc_1 = false;
		}
	}

	this -> robot_direction += IT_PERIOD * ( ( Gyro_Z_RAW / 16.4 ) + ( -1.005 * med_1 ) + ( -1 * diff_per_IT_1 ) );


}

double MPU6050::get_direction( void )
{
	while( this -> robot_direction > 360 )
		this -> robot_direction -= 360;
	while( this -> robot_direction < 0 )
		this -> robot_direction += 360;

	return this -> robot_direction + this -> robot_initial_direction;
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


void MPU6050::sort_data( double* x, int n )
{
	for( int i = 0; i < n - 1; i++ )
	{
		int j = i;
		for( int k = i; k < n; k++ )
			if( x[ k ] < x[ j ] ) j = k;
		if( i < j )
		{
			double v = x[ i ];
			x[ i ] = x [ j ];
			x[ j ] = v;
		}

	}
	return;
}

double MPU6050::calc_mode( int* array, int size )
{

	int mode;              // これまでに調べた中での最頻値
	int count_max = 0;     // これまでに調べた登場回数の中で最大のもの

	for ( int  i = 0; i < size; ++i )
	{

		int count = 1;
		for ( int j = i + 1; j < size; ++j)
		{
			if (array[i] == array[j])
			{
				++count;
			}
		}

		if (count_max <= count)
		{
			count_max = count;
			mode = array[i];
		}
	}

	    return mode;

}

