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
#include "Rope.hpp"
#include "main.h"

bool CW_run = false;
bool force_stop = false;
int last_encoder_pos = 0;

void Controller::NOP(void)
{
	PWM* pwm = new PWM();

	pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );

	delete pwm;
}

void Controller::X(void) //Rotate
{
	if( CW_run == true ) return; //You can push X, only once.

		Function* function = new Function();
		Rope* rope = new Rope();

		if( CW_run == false && rope -> encoder_read_5() != last_encoder_pos )
		{
			CW_run = true;
		}

		while( CW_run == true )
		{
			if( rope -> encoder_read_5() > 1024 )
			{
				function -> drive_motor_Rope(5, CW, 520, false);

				for(int i=0;i<100;++i)
				{
					HAL_Delay(1);
					if( force_stop == true ) return;
				}
			}
			else
			{
				function -> drive_motor_Rope(5, CW, 1080, false);

				for(int i=0;i<100;++i)
				{
					HAL_Delay(1);
					if( force_stop == true ) return;
				}
			}
		}

		delete function;
		delete rope;
}

void Controller::Y(void) //Debug
{
	Rope* rope = new Rope();

	int now_encoder_pos = rope -> encoder_read_5();
	Debug::TTO((uint8_t*)&last_encoder_pos, "prv ", &huart2);
	Debug::TTO((uint8_t*)&now_encoder_pos, "now ", &huart2);

	delete rope;
}

void Controller::A(void) //Stop all.
{
	Function* function = new Function();
	Rope* rope = new Rope();

	CW_run = false;
	force_stop = true;
	function -> drive_motor_Rope(5, BRAKE, 0, true);
	last_encoder_pos = rope -> encoder_read_5();

	delete function;
	delete rope;
}

void Controller::B(void){ //CWの2重跳び
	Function* function = new Fnction();
	Rope* rope = new Rope();

	delete funtion;
	delete rope;
}

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
