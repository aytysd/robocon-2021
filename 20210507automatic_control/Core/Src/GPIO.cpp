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
#include "main.h"

int GPIO::count = 0;
	bool GPIO::allow = false;
	int GPIO::angle[2] = {0,0};
	int GPIO::plus = 1;

void GPIO::identify(uint16_t GPIO_Pin){
	switch(GPIO_Pin){
	case GPIO_PIN_0:
		this -> GPIO_PIN_0_func();
		break;
	case GPIO_PIN_1:
		this -> GPIO_PIN_1_func();
		break;
	case GPIO_PIN_2:
		this -> GPIO_PIN_2_func();
		break;
	case GPIO_PIN_3:
		this -> GPIO_PIN_3_func();
		break;
	case GPIO_PIN_4:
		this -> GPIO_PIN_4_func();
		break;
	case GPIO_PIN_5:
		this -> GPIO_PIN_5_func();
		break;
	case GPIO_PIN_6:
		this -> GPIO_PIN_6_func();
		break;
	case GPIO_PIN_7:
		this -> GPIO_PIN_7_func();
		break;
	case GPIO_PIN_8:
		this -> GPIO_PIN_8_func();
		break;
	case GPIO_PIN_9:
		this -> GPIO_PIN_9_func();
		break;
	case GPIO_PIN_10:
		this -> GPIO_PIN_10_func();
		break;
	case GPIO_PIN_11:
		this -> GPIO_PIN_11_func();
		break;
	case GPIO_PIN_12:
		this -> GPIO_PIN_12_func();
		break;
	case GPIO_PIN_13:
		this -> GPIO_PIN_13_func();
		break;
	case GPIO_PIN_14:
		this -> GPIO_PIN_14_func();
		break;
	case GPIO_PIN_15:
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
