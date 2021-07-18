/*
 * Controller_Tomioka.cpp
 *
 *  Created on: 8 Jul 2021
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

#include "Controller.hpp"
#include "Function.hpp"
#include "Debug.hpp"
#include "main.h"

int max_angular_velocity = 360;

void Controller::NOP(void)
{
	PWM* pwm = new PWM();

	pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );

	delete pwm;
}

void Controller::X(void) //right rotation 720(rad/s)
{
	Debug* debug = new Debug();
	Function* function = new Function();

	char string[10];
	char output[10];
	sprintf(output, "CW%d\r\n", max_angular_velocity);

	for( int i = 0; i < max_angular_velocity; i += 90)
	{
		debug -> TTO((uint16_t*)max_angular_velocity, &output, &huart2);
		function -> drive_motor_Rope(5, CW, (uint16_t*)i, false);
		HAL_Delay(2000);
	}

	delete function;
	delete debug;
}

void Controller::Y(void) //left rotation 720(rad/s)
{
	Debug* debug = new Debug();
		Function* function = new Function();

		char string[10];
		char output[10];
		sprintf(output, "CW%d\r\n", max_angular_velocity);

		for( int i = 0; i < max_angular_velocity; i += 90)
		{
			debug -> TTO((uint16_t*)max_angular_velocity, &output, &huart2);
			function -> drive_motor_Rope(5, CCW, (uint16_t*)i, false);
			HAL_Delay(2000);
		}

		delete function;
		delete debug;
}

void Controller::A(void) //stop rotation
{
	Function* function = new Function();
	function -> drive_motor_Rope(5, BRAKE, 720, true);

	delete function;
}
void Controller::B(void){}

void Controller::LB(void){}
void Controller::RB(void){}
void Controller::LT(void){}
void Controller::RT(void){}
void Controller::START(void){}
void Controller::BACK(void){}

void Controller::LSU(void){}
void Controller::LSL(void){}
void Controller::LSR(void){}
void Controller::LSD(void){}
void Controller::LSUL(void){}
void Controller::LSUR(void){}
void Controller::LSDR(void){}
void Controller::LSDL(void){}

void Controller::CSU(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 500, 90, 0, 0, E_move_status::MOVE );

	  delete pwm;

}
void Controller::CSR(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 500, 0, 0, 0, E_move_status::MOVE );

	  delete pwm;


}
void Controller::CSL(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 500, 180, 0, 0, E_move_status::MOVE );

	  delete pwm;


}
void Controller::CSD(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 500, 270, 0, 0, E_move_status::MOVE );

	  delete pwm;

}
void Controller::CSUL(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 500, 135, 0, 0, E_move_status::MOVE );

	  delete pwm;

}
void Controller::CSUR(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 500, 45, 0, 0, E_move_status::MOVE );

	  delete pwm;

}
void Controller::CSDL(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 500, 225, 0, 0, E_move_status::MOVE );

	  delete pwm;
}
void Controller::CSDR(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 500, 315, 0, 0, E_move_status::MOVE );

	  delete pwm;

}


void Controller::RSU(void){}
void Controller::RSR(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 0, 0, 300, 0, E_move_status::MOVE );

	  delete pwm;

}
void Controller::RSL(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 0, 0, -300, 0, E_move_status::MOVE );

	  delete pwm;

}
void Controller::RSD(void){}
void Controller::RSUL(void){}
void Controller::RSUR(void){}
void Controller::RSDR(void){}
void Controller::RSDL(void){}
