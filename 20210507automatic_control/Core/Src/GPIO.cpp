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
#include <GPIO.hpp>
#include "Self_Pos.hpp"
#include "Gyro.hpp"
#include "main.h"
#include "Debug.hpp"

UART_HandleTypeDef* UART = &huart2;

int GPIO::count = 0;
bool GPIO::allow = false;
int GPIO::angle[2] = {0,0};
int GPIO::plus = 1;

void GPIO::identify( uint16_t GPIO_Pin )
	{
	switch( GPIO_Pin )
	{
	case GPIO_PIN_0:
		Debug::TTO_addr( &GPIO_Pin, "0", UART );
		this -> GPIO_PIN_0_func();
		break;
	case GPIO_PIN_1:
		Debug::TTO_addr( &GPIO_Pin, "1", UART );
		this -> GPIO_PIN_1_func();
		break;
	case GPIO_PIN_2:
		Debug::TTO_addr( &GPIO_Pin, "2", UART );
		this -> GPIO_PIN_2_func();
		break;
	case GPIO_PIN_3:
		Debug::TTO_addr( &GPIO_Pin, "3", UART );
		this -> GPIO_PIN_3_func();
		break;
	case GPIO_PIN_4:
		Debug::TTO_addr( &GPIO_Pin, "4", UART );
		this -> GPIO_PIN_4_func();
		break;
	case GPIO_PIN_5:
		Debug::TTO_addr( &GPIO_Pin, "5", UART );
		this -> GPIO_PIN_5_func();
		break;
	case GPIO_PIN_6:
		Debug::TTO_addr( &GPIO_Pin, "6", UART );
		this -> GPIO_PIN_6_func();
		break;
	case GPIO_PIN_7:
		Debug::TTO_addr( &GPIO_Pin, "7", UART );
		this -> GPIO_PIN_7_func();
		break;
	case GPIO_PIN_8:
		Debug::TTO_addr( &GPIO_Pin, "8", UART );
		this -> GPIO_PIN_8_func();
		break;
	case GPIO_PIN_9:
		Debug::TTO_addr( &GPIO_Pin, "9", UART );
		this -> GPIO_PIN_9_func();
		break;
	case GPIO_PIN_10:
		Debug::TTO_addr( &GPIO_Pin, "10", UART );
		this -> GPIO_PIN_10_func();
		break;
	case GPIO_PIN_11:
		Debug::TTO_addr( &GPIO_Pin, "11", UART );
		this -> GPIO_PIN_11_func();
		break;
	case GPIO_PIN_12:
		Debug::TTO_addr( &GPIO_Pin, "12", UART );
		this -> GPIO_PIN_12_func();
		break;
	case GPIO_PIN_13:
		Debug::TTO_addr( &GPIO_Pin, "13", UART );
		this -> GPIO_PIN_13_func();
		break;
	case GPIO_PIN_14:
		Debug::TTO_addr( &GPIO_Pin, "14", UART );
		this -> GPIO_PIN_14_func();
		break;
	case GPIO_PIN_15:
		Debug::TTO_addr( &GPIO_Pin, "15", UART );
		this -> GPIO_PIN_15_func();
		break;

	}
}

void GPIO::GPIO_PIN_0_func(void){};
void GPIO::GPIO_PIN_1_func(void){};
void GPIO::GPIO_PIN_2_func(void){};
void GPIO::GPIO_PIN_3_func(void){};
void GPIO::GPIO_PIN_4_func(void){};
void GPIO::GPIO_PIN_5_func(void){};
void GPIO::GPIO_PIN_6_func(void){};
void GPIO::GPIO_PIN_7_func(void){};
void GPIO::GPIO_PIN_8_func(void){};
void GPIO::GPIO_PIN_9_func(void){};
void GPIO::GPIO_PIN_10_func(void){};
void GPIO::GPIO_PIN_11_func(void)
{
	if (this->count <= 1 && this->allow) {
			Gyro *gyro = new Gyro();

			int ang = gyro->get_direction(&hi2c3);
			int low_angle = 280 - 180 * (-0.5 * this->plus + 0.5);
			int high_angle = 440 - 180 * (-0.5 * this->plus + 0.5);
			if ((low_angle <= ang && ang <= high_angle
					&& ang != Self_Pos::out_angle)
					|| (low_angle <= ang + 360 && ang + 360 <= high_angle
							&& ang != Self_Pos::out_angle)) {
				this->angle[this->count] = ang;
				this->count++;
			}
			delete gyro;
		}
};
void GPIO::GPIO_PIN_12_func(void){};
void GPIO::GPIO_PIN_13_func(void){};
void GPIO::GPIO_PIN_14_func(void)
{
	if (this->count <= 1 && this->allow) {
			Gyro *gyro = new Gyro();

			int ang = gyro->get_direction(&hi2c3);
			int low_angle = 280 - 180 * (-0.5 * this->plus + 0.5);
			int high_angle = 440 - 180 * (-0.5 * this->plus + 0.5);
			if ((low_angle <= ang && ang <= high_angle
					&& ang != Self_Pos::out_angle)
					|| (low_angle <= ang + 360 && ang + 360 <= high_angle
							&& ang != Self_Pos::out_angle)) {
				this->angle[this->count] = ang;
				this->count++;
			}
			delete gyro;
		}
};
void GPIO::GPIO_PIN_15_func(void){};
