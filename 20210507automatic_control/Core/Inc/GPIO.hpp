/*
 * GPIO.hpp
 *
 *  Created on: May 22, 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(identify which interrupt happened)
 *
 *@Input(interrupt label which you want to observe, listed in enum class E_interrupt)in(E_interrupt interrupt)of(bool get_status())
 *
 *@Output(true or false)to(get_status())
 *
 *@Attention_(once you get specific status via get_status(), the value of bool status[16] that you get will automatically be changed to false)
 *
 *@Usertouch(bool get_status())
 *
 */
#ifndef INC_GPIO_HPP_
#define INC_GPIO_HPP_

#include "main.h"

enum class E_interrupt{
	PE_SENSOR_T = 0,
	SPARE1,//cannot be used
	LIMIT_F_V3,//cannot be used
	LIMIT_L_V3,//cannot be used
	PE_SENSOR_F,
	LIMIT_F_V2,//cannot be used
	SPARE2,//cannot be used
	SPARE3,//cannot be used
	LIMIT_L_V4,//cannot be used
	SPARE5,//cannot be used
	SPARE6,//cannot be used
	SPARE7,//cannot be used
	SPARE8,//cannot be used
	PE_SENSOR_B,
	SPARE9,//cannot be used
	SPARE10,


};

class GPIO{
public:
	void identify(uint16_t GPIO_Pin);
private:

	void GPIO_PIN_0_func(void);
	void GPIO_PIN_1_func(void);
	void GPIO_PIN_2_func(void);
	void GPIO_PIN_3_func(void);
	void GPIO_PIN_4_func(void);
	void GPIO_PIN_5_func(void);
	void GPIO_PIN_6_func(void);
	void GPIO_PIN_7_func(void);
	void GPIO_PIN_8_func(void);
	void GPIO_PIN_9_func(void);
	void GPIO_PIN_10_func(void);
	void GPIO_PIN_11_func(void);
	void GPIO_PIN_12_func(void);
	void GPIO_PIN_13_func(void);
	void GPIO_PIN_14_func(void);
	void GPIO_PIN_15_func(void);


};

#endif /* INC_GPIO_HPP_ */
