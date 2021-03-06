/*
 * mpu6050.h
 *
 *  Created on: Nov 13, 2019
 *      Author: Bulanov Konstantin
 */

#ifndef INC_GY521_H_
#define INC_GY521_H_

#endif /* INC_GY521_H_ */

#include "main.h"
#include <stdint.h>
#include "General_command.hpp"

#define RAD_TO_DEG 57.295779513082320876798154814105

#define WHO_AM_I_REG 0x75
#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_CONFIG_REG 0x1B
#define GYRO_XOUT_H_REG 0x43

// Setup MPU6050
#define MPU6050_ADDR 0xD0
const uint16_t i2c_timeout = 100;
const double Accel_Z_corrector = 14418.0;

#define IT_PERIOD 0.1
#define SAMPLING_PERIOD 5
#define TESTING_PERIOD 1

class MPU6050
{
public:
	bool MPU6050_Init( void );
	void MPU6050_update_Gyro ( void );

	void set_initial_direction( E_robot_name robot );
	double get_direction( void );

	void sort_data( double* x, int n );

	double calc_mode( int* array, int size );
private:

	static double robot_direction;
	static uint16_t robot_initial_direction;
	static double table_direction;

	static bool testing;
	static bool sampling;


};


