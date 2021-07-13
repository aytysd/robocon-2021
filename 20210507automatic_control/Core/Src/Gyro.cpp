/*
 * Gyro.cpp
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

#include "Gyro.hpp"
#include "Error_Handling.hpp"
#include <General_command.hpp>
#include "main.h"
#include "Self_Pos.hpp"
#include "bno055.h"
#include "stdio.h"
#include <math.h>
#include "LED.hpp"
#include "PWM.hpp"


double Gyro::robot_direction = 0;
float Gyro::gravity = 0;
uint16_t Gyro::robot_initial_direction = 0;
double Gyro::table_direction = 0;

void Gyro::BNO055_Init_I2C(I2C_HandleTypeDef* hi2c_device)
{

	uint8_t GPwrMode 	= NormalG;   		// Gyro power mode
	uint8_t Gscale 		= GFS_2000DPS; 	// Gyro full scale
	//uint8_t Godr	 	= GODR_250Hz;  	// Gyro sample rate
	uint8_t Gbw 			= GBW_230Hz;    // Gyro bandwidth
	//
	uint8_t Ascale 		= AFS_16G;      // Accel full scale
	uint8_t APwrMode 	= NormalA;   		// Accel power mode
	uint8_t Abw 			= ABW_250Hz;    // Accel bandwidth, accel sample rate divided by ABW_divx
	//
	//uint8_t Mscale 	= MFS_4Gauss;		// Select magnetometer full-scale resolution
	uint8_t MOpMode 	= EnhancedRegular;    	// Select magnetometer perfomance mode
	uint8_t MPwrMode 	= Normal;    		// Select magnetometer power mode
	uint8_t Modr 			= MODR_30Hz;    // Select magnetometer ODR when in BNO055 bypass mode

	uint8_t PWRMode 	= Normalpwr;  	// Select BNO055 power mode
	uint8_t OPRMode 	= IMU;    	// specify operation mode for sensors [ACCONLY|MAGONLY|GYROONLY|ACCMAG|ACCGYRO|MAGGYRO|AMG|NDOF|NDOF_FMC_OFF]





	// Select BNO055 config mode
	uint8_t opr_config_mode[2] = {BNO055_OPR_MODE, CONFIGMODE};
	HAL_I2C_Master_Transmit(hi2c_device, BNO055_I2C_ADDR_HI<<1, opr_config_mode, sizeof(opr_config_mode), 10);
	HAL_Delay(10);

	// Select page 1 to configure sensors
	uint8_t conf_page1[2] = {BNO055_PAGE_ID, 0x01};
	HAL_I2C_Master_Transmit(hi2c_device, BNO055_I2C_ADDR_HI<<1, conf_page1, sizeof(conf_page1), 10);
	HAL_Delay(10);

	// Configure ACC (Page 1; 0x08)
	uint8_t conf_acc[2] = {BNO055_ACC_CONFIG, (APwrMode << 5) | (Abw << 2) | Ascale};
	HAL_I2C_Master_Transmit(hi2c_device, BNO055_I2C_ADDR_HI<<1, conf_acc, sizeof(conf_acc), 10);
	HAL_Delay(10);

	// Configure GYR
	uint8_t conf_gyro[2] = {BNO055_GYRO_CONFIG_0, Gbw << 3 | Gscale};
	HAL_I2C_Master_Transmit(hi2c_device, BNO055_I2C_ADDR_HI<<1, conf_gyro, sizeof(conf_gyro), 10);
	HAL_Delay(10);

	uint8_t conf_gyro_pwr[2] = {BNO055_GYRO_CONFIG_1, GPwrMode};
	HAL_I2C_Master_Transmit(hi2c_device, BNO055_I2C_ADDR_HI<<1, conf_gyro_pwr, sizeof(conf_gyro_pwr), 10);
	HAL_Delay(10);

	// Configure MAG
	uint8_t conf_mag_pwr[4] = {REG_WRITE, BNO055_MAG_CONFIG, 0x01, MPwrMode << 5 | MOpMode << 3 | Modr};
	HAL_I2C_Master_Transmit(hi2c_device, BNO055_I2C_ADDR_HI<<1, conf_mag_pwr, sizeof(conf_mag_pwr), 10);
	HAL_Delay(10);

	// Select BNO055 gyro temperature source
	//PutHexString(START_BYTE, BNO055_TEMP_SOURCE, 0x01 );

	// Select page 0
	uint8_t conf_page0[2] = {BNO055_PAGE_ID, 0x00};
	HAL_I2C_Master_Transmit(hi2c_device, BNO055_I2C_ADDR_HI<<1, conf_page0, sizeof(conf_page0), 10);
	HAL_Delay(10);

	// Select BNO055 sensor units (Page 0; 0x3B, default value 0x80)
	/*- ORIENTATION_MODE		 - Android					(default)
		- VECTOR_ACCELEROMETER - m/s^2  					(default)
		- VECTOR_MAGNETOMETER  - uT								(default)
		- VECTOR_GYROSCOPE     - rad/s        v		(must be configured)
		- VECTOR_EULER         - degrees					(default)
		- VECTOR_LINEARACCEL   - m/s^2        v		(default)
		- VECTOR_GRAVITY       - m/s^2						(default)
	*/
	//const char conf_units[4] = {REG_WRITE, BNO055_UNIT_SEL, 0x01, 0x82};
	//SendAccelData(USART1, (uint8_t*)conf_units);
	//HAL_Delay(50);

	// Select BNO055 system power mode (Page 0; 0x3E)
	uint8_t pwr_pwrmode[2] = {BNO055_PWR_MODE, PWRMode};
	HAL_I2C_Master_Transmit(hi2c_device, BNO055_I2C_ADDR_HI<<1, pwr_pwrmode, sizeof(pwr_pwrmode), 10);
	HAL_Delay(10);

	// Select BNO055 system operation mode (Page 0; 0x3D)
	uint8_t opr_oprmode[2] = {BNO055_OPR_MODE, OPRMode};
	HAL_I2C_Master_Transmit(hi2c_device, BNO055_I2C_ADDR_HI<<1, opr_oprmode, sizeof(opr_oprmode), 10);
	HAL_Delay(50);
}

void Gyro::BNO055_update_gravity_direction( I2C_HandleTypeDef* hi2c_device )
{

		uint8_t	imu_readings[IMU_NUMBER_OF_BYTES] = {0};
		uint8_t gyro_readings[IMU_NUMBER_OF_BYTES] = {0};

		int16_t accel_data;
		float acc_z;
		int16_t rotation;
		double yaw;


		HAL_I2C_Mem_Read(hi2c_device, BNO055_I2C_ADDR_HI<<1, BNO055_ACC_DATA_X_LSB, I2C_MEMADD_SIZE_8BIT, imu_readings, IMU_NUMBER_OF_BYTES,100);
		HAL_I2C_Mem_Read(hi2c_device, BNO055_I2C_ADDR_HI<<1, BNO055_EUL_HEADING_LSB, I2C_MEMADD_SIZE_8BIT, gyro_readings, IMU_NUMBER_OF_BYTES,100);

		accel_data = (((int16_t)((uint8_t *)(imu_readings))[5] << 8) | ((uint8_t *)(imu_readings))[4]);

		acc_z = ((float)(accel_data))/100.0f;


		rotation = (((int16_t)((uint8_t *)(gyro_readings))[1] << 8) | ((uint8_t *)(gyro_readings))[0]);      // Turn the MSB and LSB into a signed 16-bit value

		yaw = rotation / 16;

		if( hi2c_device == &hi2c1 )
		{
			this -> robot_direction = yaw;
		}
		else if( hi2c_device == &hi2c3 )
		{
			this -> table_direction = yaw;
		}

}

float Gyro::get_gravity()
{
	return this -> gravity;
}

double Gyro::get_direction( I2C_HandleTypeDef* hi2c_device )
{
	if( hi2c_device == &hi2c1 )
	{
		this -> robot_direction += this -> robot_initial_direction;
		if( this -> robot_direction > 360 ){
			this -> robot_direction -= 360;
		}

		Error_Handling* error_handling = new Error_Handling();
		error_handling -> gyro_error_handling( this -> robot_direction );
		delete error_handling;

		return this -> robot_direction;

	}
	else if( hi2c_device == &hi2c3 )
	{
		return this -> table_direction;
	}
}


void Gyro::set_initial_direction(E_robot_name robot)
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







