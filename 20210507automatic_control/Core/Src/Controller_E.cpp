/*
 * Controller_Yoshida.cpp
 *
 *  Created on: Jul 4, 2021
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
#include "PWM.hpp"
#include "Function.hpp"
#include "MPU6050.hpp"
#include "usart.h"
#include "Jump.hpp"


void Controller::NOP(void)
{
	  PWM* pwm = new PWM();

	  pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );

	  delete pwm;





}

void Controller::X(void)
{

	Function* function = new Function();

	function -> drive_motor( 1, CCW, 400, true, false );
	function -> drive_motor( 2, CW, 400, true, false );
	function -> drive_motor( 3, CW, 400, true, false );
	function -> drive_motor( 4, CCW, 400, true, false );

	delete function;
}
void Controller::Y(void)
{
	Function* function = new Function();

	for( int i = 0; i < 2; i++ )
	{
		function -> drive_motor( 1, CW, 400, true, false );
		function -> drive_motor( 2, CW, 400, true, false );
		function -> drive_motor( 3, CCW, 400, true, false );
		function -> drive_motor( 4, CCW, 400, true, false );

	}


	delete function;

}
void Controller::A(void)
{

	Function* function = new Function();

	for( int i = 0; i < 2; i++ )
	{
		function -> drive_motor( 1, CCW, 400, true, false );
		function -> drive_motor( 2, CCW, 400, true, false );
		function -> drive_motor( 3, CW, 400, true, false );
		function -> drive_motor( 4, CW, 400, true, false );

	}


	delete function;
}
void Controller::B(void)
{

	Function* function = new Function();

	function -> drive_motor( 1, CW, 400, true, false );
	function -> drive_motor( 2, CCW, 400, true, false );
	function -> drive_motor( 3, CCW, 400, true, false );
	function -> drive_motor( 4, CW, 400, true, false );

	delete function;
}

void Controller::LB(void)
{
	Function* function = new Function();

	function -> drive_motor( 1, BRAKE, 0, false, false );
	function -> drive_motor( 2, CW, 400, true, false );
	function -> drive_motor( 3, BRAKE, 0, true, false );
	function -> drive_motor( 4, CCW, 400, true, false );

	delete function;

}
void Controller::RB(void)
{
	Function* function = new Function();

	function -> drive_motor( 1, CW, 500, true, false );
	function -> drive_motor( 2, BRAKE, 0, true, false );
	function -> drive_motor( 3, CCW, 500, true, false );
	function -> drive_motor( 4, BRAKE, 0, true, false );

	delete function;

}
void Controller::LT(void)
{

	Function* function = new Function();

	function -> drive_motor( 1, CCW, 400, true, false );
	function -> drive_motor( 2, BRAKE, 0, true, false );
	function -> drive_motor( 3, CW, 400, true, false );
	function -> drive_motor( 4, BRAKE, 0, true, false );

	delete function;
}
void Controller::RT(void)
{

	Function* function = new Function();

	function -> drive_motor( 1, BRAKE, 0, true, false );
	function -> drive_motor( 2, CCW, 400, true, false );
	function -> drive_motor( 3, BRAKE, 0, true, false );
	function -> drive_motor( 4, CW, 400, true, false );

	delete function;
}
void Controller::START(void){}
void Controller::BACK(void)
{
	Jump* jump = new Jump();
	jump -> jump();
	delete jump;

}

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
	  pwm -> rotate( 300, 0 );
	  delete pwm;

}
void Controller::CSR(void)
{
	  PWM* pwm = new PWM();
	  pwm -> rotate( 300, 270 );
	  delete pwm;


}
void Controller::CSL(void)
{
	  PWM* pwm = new PWM();
	  pwm -> rotate( 300, 90 );
	  delete pwm;


}
void Controller::CSD(void)
{
	  PWM* pwm = new PWM();
	  pwm -> rotate( 300, 180 );
	  delete pwm;

}
void Controller::CSUL(void)
{
	  PWM* pwm = new PWM();
	  pwm -> rotate( 300, 45 );
	  delete pwm;

}
void Controller::CSUR(void)
{
	  PWM* pwm = new PWM();
	  pwm -> rotate( 300, 315 );
	  delete pwm;

}
void Controller::CSDL(void)
{
	  PWM* pwm = new PWM();
	  pwm -> rotate( 300, 135 );
	  delete pwm;
}
void Controller::CSDR(void)
{
	  PWM* pwm = new PWM();
	  pwm -> rotate( 300, 235 );
	  delete pwm;

}


void Controller::RSU(void){}
void Controller::RSR(void){}
void Controller::RSL(void){}
void Controller::RSD(void){}
void Controller::RSUL(void){}
void Controller::RSUR(void){}
void Controller::RSDR(void){}
void Controller::RSDL(void){}

