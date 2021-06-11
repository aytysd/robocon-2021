/*
 * LED.hpp
 *
 *  Created on: 14 May 2021
 *
 *@Author: Ayato Yoshida & Hiroto Nakakubo
 *
 *@Purpose_of_this_class:(light the LED depending on the state of the robot)
 *
 *@Input(the state of the robot)in(E_LED_status status)of(LED_output)
 *
 *@Output(void)to(LED_output)
 *
 *@Attention_(Init -> white,
 *			  Move -> Blue,
 *			  Stop -> Red,
 *			  Jump -> Green,
 *			  Turn_the_rope -> Light Blue,
 *            Connecting -> Yellow,
 *            Measurement -> Purple)
 *
 *@Usertouch(LED_output)&_(variable_name)
 *
 */
#ifndef INC_LED_HPP_
#define INC_LED_HPP_

enum class E_LED_status
{
	Done,
	Init,
	Measurement,
	Error_Handler,
	Warning,
	Wait,
	OPR_Mode,

};

class LED
{
public:
	void LED_output(E_LED_status status);
};



#endif /* INC_LED_HPP_ */
