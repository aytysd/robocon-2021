/*
 * GPIO.cpp
 *
 *  Created on: May 22, 2021
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
#include <HGPIO.hpp>
#include "main.h"
#include "Debug.hpp"
#include "Function.hpp"
#include "PWM.hpp"
#include "gpio.h"
#include "usart.h"
#include "Jump.hpp"


int HGPIO::count = 0;
bool HGPIO::allow = false;
int HGPIO::angle[2] = {0,0};
int HGPIO::plus = 1;

void HGPIO::identify( uint16_t GPIO_Pin )
{
	switch( GPIO_Pin )
	{
	case GPIO_PIN_0:
		Debug::TTO_addr( &GPIO_Pin, "GPIO0" );
		this -> GPIO_PIN_0_func();
		break;
	case GPIO_PIN_1:
		Debug::TTO_addr( &GPIO_Pin, "GPIO1" );
		this -> GPIO_PIN_1_func();
		break;
	case GPIO_PIN_2:
		Debug::TTO_addr( &GPIO_Pin, "GPIO2" );
		this -> GPIO_PIN_2_func();
		break;
	case GPIO_PIN_3:
		Debug::TTO_addr( &GPIO_Pin, "GPIO3" );
		this -> GPIO_PIN_3_func();
		break;
	case GPIO_PIN_4:
		Debug::TTO_addr( &GPIO_Pin, "GPIO4" );
		this -> GPIO_PIN_4_func();
		break;
	case GPIO_PIN_5:
		Debug::TTO_addr( &GPIO_Pin, "GPIO5" );
		this -> GPIO_PIN_5_func();
		break;
	case GPIO_PIN_6:
		Debug::TTO_addr( &GPIO_Pin, "GPIO6" );
		this -> GPIO_PIN_6_func();
		break;
	case GPIO_PIN_7:
		Debug::TTO_addr( &GPIO_Pin, "GPIO7" );
		this -> GPIO_PIN_7_func();
		break;
	case GPIO_PIN_8:
		Debug::TTO_addr( &GPIO_Pin, "GPIO8" );
		this -> GPIO_PIN_8_func();
		break;
	case GPIO_PIN_9:
		Debug::TTO_addr( &GPIO_Pin, "GPIO9" );
		this -> GPIO_PIN_9_func();
		break;
	case GPIO_PIN_10:
		Debug::TTO_addr( &GPIO_Pin, "GPIO10" );
		this -> GPIO_PIN_10_func();
		break;
	case GPIO_PIN_11:
		Debug::TTO_addr( &GPIO_Pin, "GPIO11" );
		this -> GPIO_PIN_11_func();
		break;
	case GPIO_PIN_12:
		Debug::TTO_addr( &GPIO_Pin, "GPIO12" );
		this -> GPIO_PIN_12_func();
		break;
	case GPIO_PIN_13:
		Debug::TTO_addr( &GPIO_Pin, "GPIO13" );
		this -> GPIO_PIN_13_func();
		break;
	case GPIO_PIN_14:
		Debug::TTO_addr( &GPIO_Pin, "GPIO14" );
		this -> GPIO_PIN_14_func();
		break;
	case GPIO_PIN_15:
		Debug::TTO_addr( &GPIO_Pin, "GPIO15" );
		this -> GPIO_PIN_15_func();
		break;

	}
}

//PE_Sensor_1
void HGPIO::GPIO_PIN_0_func(void)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
//	Debug::TTO_val(100, "");
	Jump* jump = new Jump();

	jump -> Jump_driver( E_Jump_status::Jump_enable );

	delete jump;
}
void HGPIO::GPIO_PIN_1_func(void)
{
	Jump* jump = new Jump();
	delete jump;
}
void HGPIO::GPIO_PIN_2_func(void){};
void HGPIO::GPIO_PIN_3_func(void){};
//PE_Sensor_3
void HGPIO::GPIO_PIN_4_func(void)
{
	Jump* jump = new Jump();

//	jump -> Jump_driver( E_Jump_status::Jump_enable );

	delete jump;

}
void HGPIO::GPIO_PIN_5_func(void){}
void HGPIO::GPIO_PIN_6_func(void){}
void HGPIO::GPIO_PIN_7_func(void){}
void HGPIO::GPIO_PIN_8_func(void){}
void HGPIO::GPIO_PIN_9_func(void){}
void HGPIO::GPIO_PIN_10_func(void){}
void HGPIO::GPIO_PIN_11_func(void){}
void HGPIO::GPIO_PIN_12_func(void)
{
	Function* function = new Function();

//	function -> drive_motor( 5, BRAKE, 0, false, true );

	delete function;
}
void HGPIO::GPIO_PIN_13_func(void)
{
	Jump* jump = new Jump();

	jump -> Jump_driver( E_Jump_status::Jump_enable );

	delete jump;
}
//PE_Sensor_2
void HGPIO::GPIO_PIN_14_func(void)
{
	Jump* jump = new Jump();

//	jump -> Jump_driver( E_Jump_status::Jump_enable );

	delete jump;
}
void HGPIO::GPIO_PIN_15_func(void){}
