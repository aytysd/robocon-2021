/*
 * Control_C.cpp
 *
 *  Created on: 1 Aug 2021
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

#include "Control.hpp"
#include "main.h"
#include "General_command.hpp"
#include "Init_Move.hpp"
#include "Line.hpp"
#include "Infinity_command.hpp"
#include "Self_Pos.hpp"
#include "Jump.hpp"
#include "LED.hpp"
#include "usart.h"
#include "PWM.hpp"
#include "Rope.hpp"
#include "Time.hpp"
#include "math.h"
#include "tim.h"
#include "Control_C.hpp"

bool Control_C::A_ready_flag = false;
bool Control_C::B_ready_flag = false;


void Control_C::control_C( void )
{
	this -> stay_jump();
	this -> cross_jump();
	this -> infinity_jump();
}

void Control_C::stay_jump( void )
{

	Control* control = new Control();
	Rope* rope = new Rope();
	Time* time = new Time();

	uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MODE_STAY_JUMP };
	this -> send_both( data );

	while( !( Control_C::A_ready_flag == true ) ){};
	Control_C::A_ready_flag = false;

	data[ 0 ] = { ( uint8_t )E_data_type::A_start };
	this -> send_both( data );

	while( abs( rope -> encoder_read_3( true ) ) < 256 ){};

	HAL_TIM_Base_Start_IT( &htim7 );
	rope -> rotate_rope( RMN, CW, 700, 500 );

	time -> reset_timer();
	while( time -> calc_time_diff() <= ( uint32_t )E_Time::stay_jump ){};

	rope -> stop_rope( RMN );
	HAL_TIM_Base_Stop_IT( &htim7 );

	data[ 0 ] = { ( uint8_t )E_data_type::stop };
	this -> send_both( data );

	delete time;
	delete rope;
	delete control;


}

void Control_C::cross_jump( void )
{

	Control* control = new Control();
	Rope* rope = new Rope();
	Time* time = new Time();

	uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MODE_CROSS_JUMP };
	this -> send_both( data );

	this -> wait_for_ab();

	data[ 0 ] = { ( uint8_t )E_data_type::A_start };
	this -> send_both( data );

	HAL_Delay( 3000 );

	data[ 0 ] = { ( uint8_t )E_data_type::B_start };
	this -> send_both( data );

	rope -> rotate_rope( RMN, CW, 700, 500 );
	HAL_TIM_Base_Start_IT( &htim7 );

	time -> reset_timer();
	while( time -> calc_time_diff() <= ( uint32_t )E_Time::cross_jump ){};

	rope -> stop_rope( RMN );
	HAL_TIM_Base_Stop_IT( &htim7 );

	data[ 0 ] = { ( uint8_t )E_data_type::stop };
	this -> send_both( data );


	delete time;
	delete rope;
	delete control;

}

void Control_C::infinity_jump( void )
{

	Control* control = new Control();
	Rope* rope = new Rope();
	Time* time = new Time();

	uint8_t data[ DATASIZE ] = { ( uint8_t )E_data_type::command, ( uint8_t )E_Flow::MODE_INFINITY_JUMP };
	this -> send_both( data );

	this -> wait_for_ab();

	data[ 0 ] = { ( uint8_t )E_data_type::A_start };
	this -> send_both( data );

	data[ 0 ] = { ( uint8_t )E_data_type::B_start };
	this -> send_both( data );

	rope -> rotate_rope( RMN, CW, 700, 500 );
	HAL_TIM_Base_Start_IT( &htim7 );

	time -> reset_timer();
	while( time -> calc_time_diff() <= ( uint32_t )E_Time::infinity ){};

	rope -> stop_rope( RMN );
	HAL_TIM_Base_Stop_IT( &htim7 );

	data[ 0 ] = { ( uint8_t )E_data_type::stop };
	this -> send_both( data );


	delete time;
	delete rope;
	delete control;

}

void Control_C::wait_for_ab( void )
{

#ifdef WITHOUT_B

	while( !( Control_C::A_ready_flag == true ) ){};

	Control_C::A_ready_flag = false;

#elif defined ( WITHOUT_A )

	while( !( Control_C::B_ready_flag == true ) ){};

	Control_C::B_ready_flag = false;


#elif defined ( WITHOUT_C )

#else

	while( !( Control_C::A_ready_flag == true && Control_C::B_ready_flag == true ) ){};

	Control_C::A_ready_flag = false;
	Control_C::B_ready_flag = false;

#endif

	HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET );

}

void Control_C::send_both( uint8_t* data )
{

	Control* control = new Control();

#ifdef WITHOUT_A
	control -> send_command( E_robot_name::B, data );

#elif defined ( WITHOUT_B )
	control -> send_command( E_robot_name::A, data );

#else
	control -> send_command( E_robot_name::B, data );
	control -> send_command( E_robot_name::A, data );

#endif

	delete control;

}
