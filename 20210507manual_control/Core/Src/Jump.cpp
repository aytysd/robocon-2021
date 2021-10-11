/*
 * Jump.cpp
 *
 *  Created on: 9 May 2021
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

#include "Jump.hpp"
#include "General_command.hpp"
#include "hGPIO.hpp"
#include "main.h"
#include "Self_Pos.hpp"
#include "math.h"
#include "function.hpp"
#include "Self_Pos.hpp"
#include "Line.hpp"
#include "Controller.hpp"
#include "usart.h"

E_Jump_status Jump::Jump_status = E_Jump_status::Jump_disable;

int16_t Jump::RS_0_90 = 0;
int16_t Jump::RS_90_180 = 0;
int16_t Jump::RS_180_270 = 0;
int16_t Jump::RS_270_0 = 0;
//bool Jump::PE_5 = false;

int Jump::rope = 0;


void Jump::Jump_driver( E_Jump_status status)
{
	this -> Jump_status = status;
}

E_Jump_status Jump::get_Jump_status( void )
{
	return this -> Jump_status;
}

void Jump::Into_Rope( void )
{
	Self_Pos* self_pos = new Self_Pos();
	Line* line = new Line();

	double distance = sqrt( pow((double)self_pos -> get_Self_Pos_X(), 2.0 ) + pow((double)self_pos -> get_Self_Pos_Y(), 2.0 ));
	double time = distance / 1000;
	int surplus;
	double start_RN;

	while( time > 0 )
	{
		time -= (double)this -> RS_90_180;
		if( time <= 0 )
		{
			surplus = 2;
			time += (double)this -> RS_90_180;
			break;
		}
		time -= (double)this -> RS_0_90;
		if( time <= 0 )
		{
			surplus = 1;
			time += (double)this -> RS_0_90;
			break;
		}
		time -= (double)this -> RS_270_0;
		if( time <= 0 )
		{
			surplus = 4;
			time += (double)this -> RS_270_0;
			break;
		}
		time -= (double)this -> RS_180_270;
		if( time <= 0 )
		{
			surplus = 3;
			time += (double)this -> RS_180_270;
			break;
		}
	}

	switch( surplus )
	{
	case 1:
		start_RN = time / (double)this -> RS_0_90 * 90;
		start_RN += 0;
		break;
	case 2:
		start_RN = time / (double)this -> RS_90_180 * 90;
		start_RN += 90;
		break;
	case 3:
		start_RN = time / (double)this -> RS_180_270 * 90;
		start_RN += 180;
		break;
	case 4:
		start_RN = time / (double)this -> RS_270_0 * 90;
		start_RN += 270;
		break;
	default:
		break;
	}

	while( abs((int)start_RN - this -> rope) < 30 ){}

	line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), 0, 0, false, false );
	while(  Line::judge == E_Line_status::MOVING ){}

	delete line;
	delete self_pos;
}

void Jump::jump( void )
{
	this -> Jump_status = E_Jump_status ::Jump_enable;
	HAL_GPIO_WritePin( GPIOC, GPIO_PIN_2, GPIO_PIN_SET );

	uint32_t start_time = HAL_GetTick();

	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_RESET );
	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_SET );// || ( ( HAL_GetTick() - start_time ) < 3000 ) );
	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_RESET );
//	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_SET );
//	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_RESET );
//	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_SET );
//	while( HAL_GPIO_ReadPin( GPIOB, GPIO_PIN_12 ) == GPIO_PIN_RESET );


	HAL_GPIO_WritePin( GPIOC, GPIO_PIN_2, GPIO_PIN_RESET );
  
	this -> Jump_status = E_Jump_status::Jump_disable;
  

//	  HAL_UART_Receive_IT( &huart4, ( uint8_t* )Controller::controller_Rxdata, sizeof( Controller::controller_Rxdata ) );

}


bool Jump::Is_centre( void )
{

	Self_Pos* self_pos = new Self_Pos();

	double distance = sqrt( ( self_pos -> get_Self_Pos_X() ^ 2 ) + ( self_pos -> get_Self_Pos_Y() ^ 2 ) );

	if( distance < 300 )
		return true;
	else
		return false;

}

void Jump::RS_calc( void )
{
	this -> mode = this -> rope / 90 + 1;
	switch( mode )
	{
	case 1:
		this -> count++;
		break;
	case 2:
		this -> count++;
		break;
	case 3:
		this -> count++;
		break;
	case 4:
		this -> count++;
		break;
	default:
		break;
	}
	if( this -> mode != this -> prev_mode )
	{
		switch( this -> prev_mode )
		{
		case 1:
			this -> RS_0_90 = 0.2 * this -> count;
			break;
		case 2:
			this -> RS_90_180 = 0.2 * this -> count;
			break;
		case 3:
			this -> RS_180_270 = 0.2 * this -> count;
			break;
		case 4:
			this -> RS_270_0 = 0.2 * this -> count;
			break;
		default:
			break;
		}
		this -> count = 0;
	}
	this -> prev_mode = this -> mode;
}

//void Jump::PE_Sensor( int PE_num )
//{
//	switch( PE_num )
//	{
//	case 1:
//		this -> PE_1 = true;
//		break;
//	case 2:
//		this -> PE_2 = true;
//		break;
//	case 3:
//		this -> PE_3 = true;
//		break;
//	case 4:
//		this -> PE_4 = true;
//		break;
//	case 5:
//		this -> PE_5 = true;
//		break;
//	default:
//		break;
//	}
//}
//
//bool Jump::get_PE_status( int func )
//{
//	switch( func )
//	{
//	case PE_Jump:
//		if(( this -> PE_1 == true ) || ( this -> PE_2 == true ) || ( this -> PE_3 == true ))
//		{
//			this -> PE_init();
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//		break;
//	case PE_Self_Pos:
//		if(( this -> PE_4 == true ) || ( this -> PE_5 == true ))
//		{
//			this -> PE_init();
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//		break;
//	default:
//		break;
//	}
//}
//
//void Jump::PE_init()
//{
//	this -> PE_1 = false;
//	this -> PE_2 = false;
//	this -> PE_3 = false;
//	this -> PE_4 = false;
//	this -> PE_5 = false;
//}
