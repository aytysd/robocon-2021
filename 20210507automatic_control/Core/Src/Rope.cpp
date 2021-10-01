/*
 * Rope.cpp
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

#include "main.h"
#include "Rope.hpp"
#include "Debug.hpp"
#include "Function.hpp"
#include "PWM.hpp"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "Control.hpp"


int Rope::over_flow_cnt_3 = -1;

bool Rope::run_C = false;
bool force_stop = false;
//int last_encoder_pos = 0;

int Rope::encoder_read_3( bool rope )
{
	int enc_buff = this -> over_flow_cnt_3 * 0x10000 + TIM3 -> CNT;
	Debug::TTO_val(enc_buff, "enc:" );

	while( enc_buff > 2048 )
		enc_buff -= 2048;
	while( enc_buff < 0 )
		enc_buff += 2048;

	if( rope == true){}
	else if( rope == false )
	{
		enc_buff *= 0.17578;
		enc_buff = 360 -enc_buff;
		if( enc_buff == 0 ){ enc_buff = 360; }
	}
	return enc_buff;
}


//rotate_rope(5, CW, 1040, 520);
//void Rope::rotate_rope(uint8_t motor_number, uint8_t direction, uint16_t down_speed, uint16_t up_speed)
//{
//	if( Rope::run_C == true ) return;
//
//	Function* function = new Function();
//	Rope* rope = new Rope();
//
//	if( Rope::run_C == false /*&& rope -> encoder_read_3() != last_encoder_pos*/) Rope::run_C = true;
//
//	while( run_C == true )
//	{
//		if( rope -> encoder_read_3() > 1024 )
//		{
//			function -> drive_motor_Rope(motor_number, direction, up_speed, false);
//
//			for(int i=0;i<100;++i)
//			{
//				HAL_Delay(1);
//				if( force_stop == true ) return;
//			}
//		}
//		else
//		{
//			function -> drive_motor_Rope(motor_number, direction, down_speed, false);
//
//			for(int i = 0; i < 100; ++i)
//			{
//				HAL_Delay(1);
//				if( force_stop == true ) return;
//			}
//		}
//		Debug::TTO_val( encoder_read_3(), "encoder:", &huart2);
//	}
//
//	delete function;
//	delete rope;
//}

void Rope::rotate_rope(uint8_t motor_number, uint8_t direction, uint16_t down_speed, uint16_t up_speed)
{
	if( Rope::run_C == true )
		return;

	Function* function = new Function();

	if( Rope::run_C == false /*&& rope -> encoder_read_3() != last_encoder_pos*/)
		Rope::run_C = true;

	function -> drive_motor_Rope( motor_number, direction, 1000, false);
	while( this -> encoder_read_3( true ) < 1024){}

	while( Rope::run_C == true )
	{
		if(( this -> encoder_read_3( true ) > 1536 ) || (this -> encoder_read_3( true ) < 512 ))
		{
			function -> drive_motor_Rope( motor_number, direction, down_speed, false);
		}
		else if(( this -> encoder_read_3( true ) > 512 ) && (this -> encoder_read_3( true ) < 1536))
		{
			function -> drive_motor_Rope(motor_number, direction, up_speed, false);
		}
		Debug::TTO_val( encoder_read_3( true ), "encoder:" );
	}

	delete function;
}

//stop_rotate(5);
void Rope::stop_rope(uint8_t motor_number)
{
	Function* function = new Function();

	Rope::run_C = false;
	force_stop = true;
	function -> drive_motor_Rope(motor_number, BRAKE, 0, true);
	//last_encoder_pos = rope -> encoder_read_3();

	delete function;
}

void Rope::Encoder_val_TX( void )
{
	Control* control = new Control();

	uint8_t en_1 = ( 0b1111111100000000 & this -> encoder_read_3( true ) ) >> 8;
	uint8_t en_2 = ( 0b0000000011111111 & this -> encoder_read_3( true ) );

	uint8_t TXdata_rope[8] = { ( uint8_t )E_data_type::rope, en_1, en_2 };

	control -> send_command( E_robot_name::A, TXdata_rope );
	control -> send_command( E_robot_name::B, TXdata_rope );

	delete control;

}

void Rope::Encoder_val_RX( int* rope, uint8_t* received_data )
{
	*rope = 0;

	*rope = received_data[ 1 ] << 8;
	*rope |= received_data[ 2 ];

}
