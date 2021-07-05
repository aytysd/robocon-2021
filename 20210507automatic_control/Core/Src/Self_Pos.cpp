/*
 * Self_Pos.cpp
 *
 *  Created on: 7 May 2021
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



#include <General_command.hpp>
#include "main.h"
#include "Self_Pos.hpp"
#include "bno055.h"
#include "stdio.h"
#include <math.h>
#include "Error_Handling.hpp"
#include "LED.hpp"
#include "PWM.hpp"

int Self_Pos::Self_Pos_X = 0;//(mm)
int Self_Pos::Self_Pos_Y = 0;//(mm)
//----------------------------------------------------------------------
//Self_Pos* self_pos = new Self_Pos();

int Self_Pos::get_Self_Pos_X()
{
	return this -> Self_Pos_X;
}

int Self_Pos::get_Self_Pos_Y()
{
	return this -> Self_Pos_Y;
}

void Self_Pos::add_Self_Pos( int add_x, int add_y )
{
	this -> Self_Pos_Y += add_x;
	this -> Self_Pos_X += add_y;

}

void Self_Pos::set_initial_pos(E_robot_name robot)
{
	switch(robot)
	{
	case E_robot_name::A:

		this -> Self_Pos_X = -2643;
		this -> Self_Pos_Y = 2643;

		break;
	case E_robot_name::B:

		this -> Self_Pos_X = -2643;
		this -> Self_Pos_Y = -2643;

		break;
	case E_robot_name::C:

		this -> Self_Pos_X = 2643;
		this -> Self_Pos_Y = -2643;

		break;

	case E_robot_name::NONE:

		this -> Self_Pos_X = 2643;
		this -> Self_Pos_Y = -2643;

		break;
	}

}
//delete self_pos;
//-------------------------------------
//Self_Pos* self_pos = new Self_Pos();
void Self_Pos::update_self_pos(void)
{
	Self_Pos::Gyro* gyro = new Self_Pos::Gyro();
	
	int d1 = 2 * OD_RADIUS * M_PI * ( (double)this -> encoder_read_5() / 2048 ); //encoder5_moving distance(mm) 55.5=wheel radius 2048=encoder resolution
	int d2 = 2 * OD_RADIUS * M_PI * ( (double)this -> encoder_read_2() / 2048 ); //encoder5_moving distance(mm) 55.5=wheel radius 2048=encoder resolution


	this -> Self_Pos_X += d1 * cos( (double)gyro -> get_direction() * M_PI / 180) - d2 * sin( (double)gyro -> get_direction() * M_PI / 180);//X_coordinate
	this -> Self_Pos_Y += d1 * sin( (double)gyro -> get_direction() * M_PI / 180) + d2 * cos( (double)gyro -> get_direction() * M_PI / 180);//Y_coordinate


	char output[10];
	sprintf( output, "X:%d\r\n", this -> Self_Pos_X );
	HAL_UART_Transmit(&huart1, (uint8_t*)output, sizeof(output), 100);
	sprintf( output, "Y:%d\r\n", this -> Self_Pos_Y );
	HAL_UART_Transmit(&huart1, (uint8_t*)output, sizeof(output), 100);



	delete gyro;
}
//delete self_pos;
//---------------------------------------
void Self_Pos::update_self_pos_ToF()
{
	ToF* tof = new ToF();
	this -> Self_Pos_X;
	this -> Self_Pos_Y;
	delete tof;
}
//---------------------------------------
int Self_Pos::encoder_read_5(void)
{
	 static int prev_encoder_value = 0;
	 uint32_t enc_buff_5 = TIM5 -> CNT;
	 int encoder_value = 0;

/*
	 Error_Handling* error_handling = new Error_Handling();
	 error_handling -> TIM5_error_handling();
	 delete error_handling;
*/


	 if( enc_buff_5 <= 2147483647 )
	 {
		 encoder_value = enc_buff_5;
	 }
	 else if( enc_buff_5 >= 2147483649 )
	 {
		 encoder_value = enc_buff_5 - 4294967295;
	 }


	 prev_encoder_value = encoder_value;

	 return encoder_value - prev_encoder_value;

/*
	  if (enc_buff_5 > 400000000)
	  {
		int Envalue5=enc_buff_5-4294967295;
		this -> encoder5=+Envalue5;
	    return this -> encoder5;
	  }
	  else
	  {
		this -> encoder5=+enc_buff_5;
	    return this -> encoder5;
	  }
*/
}
//------------------------------------------------------
int Self_Pos::encoder_read_2(void)
{

	 static int prev_encoder_value = 0;
	 uint32_t enc_buff_2 = TIM2 -> CNT;
	 int encoder_value = 0;

/*
	 Error_Handling* error_handling = new Error_Handling();
	 error_handling -> TIM2_error_handling();
	 delete error_handling;
*/


	 if( enc_buff_2 <= 2147483647 )
	 {
		 encoder_value = enc_buff_2;
	 }
	 else if( enc_buff_2 >= 2147483649 )
	 {
		 encoder_value = enc_buff_2 - 4294967295;
	 }


	 prev_encoder_value = encoder_value;

	 return encoder_value - prev_encoder_value;



/*
	  TIM2->CNT = 0;
	  if (enc_buff_2 > 400000000)
	  {
		int Envalue2=enc_buff_2-4294967295;
		this -> encoder2=+Envalue2;
	    return this -> encoder2;
	  }
	  else
	  {
		this -> encoder2=+enc_buff_2;
	    return this ->encoder2;
	  }
*/
}

int Self_Pos::calc_diff( int prev_x, int prev_y, int current_x, int current_y )
{
	int x_diff = current_x - prev_x;
	int y_diff = current_y - prev_y;

	int diff = sqrt( pow( x_diff, 2 ) + pow( y_diff, 2 ) );

	return diff;
}

int Self_Pos::Self_Pos_config(void)
{
	uint8_t reset_pos = 0;
	int diff = 0;
	char output[10];

	PWM* pwm = new PWM();

	if( this -> get_Self_Pos_X() > 0 )
	{
		reset_pos |= true;
	}
	else
	{
		reset_pos |= true << 1;
	}

	if( this -> get_Self_Pos_Y() > 0 )
	{
		reset_pos |= true << 2;
	}
	else
	{
		reset_pos |= true << 3;
	}

	switch( reset_pos )
	{
	case 0b00000101:
	{

		pwm -> rotate( 500, 270 );

		pwm -> V_output( 500, 0, 0, 270, E_move_status::MOVE );
		while( (HAL_GPIO_ReadPin(LIMIT_F_V2_GPIO_Port, LIMIT_F_V2_Pin) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_F_V3_GPIO_Port, LIMIT_F_V3_Pin ) == GPIO_PIN_RESET) );
		pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );
		HAL_Delay(2000);

		pwm -> V_output( 500, 90, 0, 270, E_move_status::MOVE );
		while( (HAL_GPIO_ReadPin(LIMIT_L_V3_GPIO_Port, LIMIT_L_V3_Pin) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_L_V4_GPIO_Port, LIMIT_L_V4_Pin ) == GPIO_PIN_RESET) );
		pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );


		int prev_x = this -> get_Self_Pos_X();
		int prev_y = this -> get_Self_Pos_Y();

		this -> set_initial_pos( E_robot_name::NONE );

		diff = this -> calc_diff( prev_x, prev_y, this -> get_Self_Pos_X(), this -> get_Self_Pos_Y() );

		break;
	}
	case 0b00001001:
	{
		pwm -> rotate( 500, 180 );

		pwm -> V_output( 500, 0, 0, 180, E_move_status::MOVE );
		while( (HAL_GPIO_ReadPin(LIMIT_L_V3_GPIO_Port, LIMIT_L_V3_Pin) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_L_V4_GPIO_Port, LIMIT_L_V4_Pin ) == GPIO_PIN_RESET) );
		pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );
		HAL_Delay(2000);


		pwm -> V_output( 500, 270, 0, 180, E_move_status::MOVE );
		while( (HAL_GPIO_ReadPin(LIMIT_F_V2_GPIO_Port, LIMIT_F_V2_Pin) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_F_V3_GPIO_Port, LIMIT_F_V3_Pin ) == GPIO_PIN_RESET) );
		pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );


		int prev_x = this -> get_Self_Pos_X();
		int prev_y = this -> get_Self_Pos_Y();


		this -> set_initial_pos( E_robot_name::C );

		diff = this -> calc_diff( prev_x, prev_y, this -> get_Self_Pos_X(), this -> get_Self_Pos_Y() );

		break;
	}
	case 0b00000110:
	{
		pwm -> rotate( 500, 0 );

		pwm -> V_output( 500, 180, 0, 0, E_move_status::MOVE );
		while( (HAL_GPIO_ReadPin(LIMIT_L_V3_GPIO_Port, LIMIT_L_V3_Pin) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_L_V4_GPIO_Port, LIMIT_L_V4_Pin ) == GPIO_PIN_RESET) );
		pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );
		HAL_Delay(2000);


		pwm -> V_output( 500, 90, 0, 0, E_move_status::MOVE );
		while( (HAL_GPIO_ReadPin(LIMIT_F_V2_GPIO_Port, LIMIT_F_V2_Pin) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_F_V3_GPIO_Port, LIMIT_F_V3_Pin ) == GPIO_PIN_RESET) );
		pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );


		int prev_x = this -> get_Self_Pos_X();
		int prev_y = this -> get_Self_Pos_Y();


		this -> set_initial_pos( E_robot_name::A );

		diff = this -> calc_diff( prev_x, prev_y, this -> get_Self_Pos_X(), this -> get_Self_Pos_Y() );

		break;
	}
	case 0b00001010:
	{
		pwm -> rotate( 500, 90 );

		pwm -> V_output( 500, 180, 0, 90, E_move_status::MOVE );
		while( (HAL_GPIO_ReadPin(LIMIT_F_V2_GPIO_Port, LIMIT_F_V2_Pin) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_F_V3_GPIO_Port, LIMIT_F_V3_Pin ) == GPIO_PIN_RESET) );
		pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );
		HAL_Delay(2000);


		pwm -> V_output( 500, 270, 0, 90, E_move_status::MOVE );
		while( (HAL_GPIO_ReadPin(LIMIT_L_V3_GPIO_Port, LIMIT_L_V3_Pin) == GPIO_PIN_RESET ) || ( HAL_GPIO_ReadPin( LIMIT_L_V4_GPIO_Port, LIMIT_L_V4_Pin ) == GPIO_PIN_RESET) );
		pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );


		int prev_x = this -> get_Self_Pos_X();
		int prev_y = this -> get_Self_Pos_Y();


		this -> set_initial_pos( E_robot_name::B );

		diff = this -> calc_diff( prev_x, prev_y, this -> get_Self_Pos_X(), this -> get_Self_Pos_Y() );

		break;
	}
	}

	delete pwm;

	sprintf( output, "%d\r\n", diff );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );

	return diff;

}

//-------------------------------------------------------------------------
void Self_Pos::Gyro::BNO055_Init_I2C(I2C_HandleTypeDef* hi2c_device)
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

void Self_Pos::Gyro::BNO055_update_gravity_direction(I2C_HandleTypeDef* hi2c_device)
{

	uint8_t	imu_readings[IMU_NUMBER_OF_BYTES];
	uint8_t gyro_readings[IMU_NUMBER_OF_BYTES];

	int16_t accel_data;
	float acc_z;
	int16_t rotation;
	int16_t yaw;
	char output[10];


	HAL_I2C_Mem_Read(hi2c_device, BNO055_I2C_ADDR_HI<<1, BNO055_ACC_DATA_X_LSB, I2C_MEMADD_SIZE_8BIT, imu_readings, IMU_NUMBER_OF_BYTES,100);
	HAL_I2C_Mem_Read(hi2c_device, BNO055_I2C_ADDR_HI<<1, BNO055_EUL_HEADING_LSB, I2C_MEMADD_SIZE_8BIT, gyro_readings, IMU_NUMBER_OF_BYTES,100);

	accel_data = (((int16_t)((uint8_t *)(imu_readings))[5] << 8) | ((uint8_t *)(imu_readings))[4]);

	acc_z = ((float)(accel_data))/100.0f;


	rotation = (((int16_t)((uint8_t *)(gyro_readings))[1] << 8) | ((uint8_t *)(gyro_readings))[0]);      // Turn the MSB and LSB into a signed 16-bit value

	yaw = rotation / 16;

	this -> gravity = acc_z;
	this -> direction = yaw;

	sprintf( output, "%d\r\n", this -> direction );
	HAL_UART_Transmit( &huart1, (uint8_t*)output, sizeof(output), 100 );


/*
	sprintf(output_2, "%lf\r\n",acc_z);
	HAL_UART_Transmit(&huart2, (uint8_t*)output_2, sizeof(output_2),100);
*/


}

float Self_Pos::Gyro::get_gravity()
{
	return this -> gravity;
}

uint16_t Self_Pos::Gyro::get_direction()
{

	this -> direction += this -> initial_direction;
	if( this -> direction > 360 ){
		this -> direction -= 360;
	}

	Error_Handling* error_handling = new Error_Handling();
	error_handling -> gyro_error_handling( this -> direction );
	delete error_handling;

	return this -> direction;
}


void Self_Pos::Gyro::set_initial_direction(E_robot_name robot)
{
	switch(robot)
	{
	case E_robot_name::A:
		this -> initial_direction = 0;
		break;
	case E_robot_name::B:
		this -> initial_direction = 90;
		break;
	case E_robot_name::C:
		this -> initial_direction = 180;
		break;
	default:
		break;
	}
}


uint16_t Self_Pos::Gyro::direction = 0;
float Self_Pos::Gyro::gravity = 0;
uint16_t Self_Pos::Gyro::initial_direction = 0;


