/*
 * Controller.cpp
 *
 *  Created on: May 9, 2021
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
#include <Controller.hpp>
#include "main.h"
#include "General_command.hpp"
#include "Function.hpp"
#include "PWM.hpp"
#include "stdio.h"

uint8_t Controller::controller_Rxdata[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void Controller::check_array(void)
{
	char output[5];
	for( int i = 0; i<8; i++)
	{
		sprintf(output, "%d\r\n", Controller::controller_Rxdata[i]);
		HAL_UART_Transmit(&huart2, (uint8_t*)output, sizeof(output), 100);
	}
}

void Controller::identify()
{
	this -> check_array();
	if( this -> identify_NOP() == false )
	{
		this -> identify_ABXY_button();
		this -> identify_SUB_button();
		this -> identify_LS_SB();
		this -> identify_CS();
		this -> identify_RS();

	}

}

bool Controller::identify_NOP()
{
	uint8_t initial_value[8] = {128, 0, 0, 64, 64, 64, 64, 0};
	uint8_t count = 0;

	for( int i = 0; i<8; i++)
	{
		if( this -> controller_Rxdata[i] == initial_value[i] )
		{
			count++;
		}
	}

	if( count == 8 )
	{
		this -> NOP();
		char str[8] = "NOP\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);
		return true;
	}

	return false;

}

void Controller::identify_ABXY_button()
{
	if( (this -> controller_Rxdata[1] & 0b00000001) == true )
	{
		this -> X();
		char str[8] = "X\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

	if( (this -> controller_Rxdata[2] & 0b00010000) >> 4 == true )
	{
		this -> Y();
		char str[8] = "Y\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

	if( (this -> controller_Rxdata[2] & 0b00100000) >> 5 == true )
	{
		this -> A();
		char str[8] = "A\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

	if( (this -> controller_Rxdata[2] & 0b01000000) >> 6 == true )
	{
		this -> B();
		char str[8] = "B\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}



}

void Controller::identify_SUB_button()
{

	if( (this -> controller_Rxdata[1] & 0b00010000) >> 4 == true)
	{
		this -> RT();
		char str[8] = "RT\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

	if( (this -> controller_Rxdata[1] & 0b00000010) >> 1 == true)
	{
		this -> LB();
		char str[8] = "LB\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

	if( (this -> controller_Rxdata[1] & 0b00001000) >> 3 == true)
	{
		this -> RB();
		char str[8] = "RB\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

	if( (this -> controller_Rxdata[1] & 0b00000100) >> 2 == true)
	{
		this -> LT();
		char str[8] = "LT\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

	if( (this -> controller_Rxdata[1] & 0b00100000) >> 5 == true)
	{
		this -> START();
		char str[8] = "START\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

	if( (this -> controller_Rxdata[1] & 0b01000000) >> 6 == true)
	{
		this -> BACK();
		char str[8] = "BACK\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}



}

void Controller::identify_LS_SB()
{

	if( (this -> controller_Rxdata[2] & 0b00001000) >> 3 == true && (this -> controller_Rxdata[2] & 0b00000100) >> 2 == true )
	{
		this -> BACK();
		char str[8] = "BACK\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);
		return;
	}

	if( (this -> controller_Rxdata[2] & 0b00000010) >> 1 == true && (this -> controller_Rxdata[2] & 0b00000001) == true)
	{
		this -> START();
		char str[8] = "START\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);
		return;
	}


	if( (this -> controller_Rxdata[2] & 0b00000001) == true)
	{
		this -> LSU();
		char str[8] = "LSU\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

	if( (this -> controller_Rxdata[2] & 0b00000010) >> 1 == true)
	{
		this -> LSD();
		char str[8] = "LSD\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

	if( (this -> controller_Rxdata[2] & 0b00000100) >> 2 == true)
	{
		this -> LSR();
		char str[8] = "LSR\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

	if( (this -> controller_Rxdata[2] & 0b00001000) >> 3 == true)
	{
		this -> LSL();
		char str[8] = "LSL\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

	}

}


void Controller::identify_CS()
{
	if( this -> controller_Rxdata[3] != this -> controller_Rxdata[4])
	{
		if( ((this -> controller_Rxdata[3] + this -> controller_Rxdata[4]) & 0b01000000) >> 6 == true)
		{
			if( this -> controller_Rxdata[3] > this -> controller_Rxdata[4] )
			{
				this -> CSU();
				char str[8] = "CSU\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

			}
			else
			{
				this -> CSL();
				char str[8] = "CSL\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

			}
		}
		else
		{
			if( this -> controller_Rxdata[3] > this -> controller_Rxdata[4] )
			{
				this -> CSR();
				char str[8] = "CSR\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

			}
			else
			{
				this -> CSD();
				char str[8] = "CSD\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

			}

		}

	}


}

void Controller::identify_RS()
{
	if( this -> controller_Rxdata[5] != this -> controller_Rxdata[6])
	{
		if( ((this -> controller_Rxdata[5] + this -> controller_Rxdata[6]) & 0b01000000) >> 6 == true)
		{
			if( this -> controller_Rxdata[5] > this -> controller_Rxdata[6] )
			{
				this -> RSU();
				char str[8] = "RSU\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

			}
			else
			{
				this -> RSL();
				char str[8] = "RSL\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

			}
		}
		else
		{
			if( this -> controller_Rxdata[5] > this -> controller_Rxdata[6] )
			{
				this -> RSR();
				char str[8] = "RSR\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

			}
			else
			{
				this -> RSD();
				char str[8] = "RSD\r\n";
				HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

			}

		}

	}


}

/*
void Controller::NOP(void){}

void Controller::X(void){}
void Controller::Y(void){}
void Controller::A(void){}
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

void Controller::CSU(void){}
void Controller::CSR(void){}
void Controller::CSL(void){}
void Controller::CSD(void){}

void Controller::RSU(void){}
void Controller::RSR(void){}
void Controller::RSL(void){}
void Controller::RSD(void){}
*/

/*void Controller::NOP(void){}

void Controller::X(void)
{
	target_speed -= 100;
	sprintf(output, "%d\r\n", target_speed);
	HAL_UART_Transmit(&huart2, (uint8_t*)output, sizeof(output), 100);
}
void Controller::Y(void){}
void Controller::A(void){}
void Controller::B(void)
{
	target_speed += 100;
	sprintf(output, "%d\r\n", target_speed);
	HAL_UART_Transmit(&huart2, (uint8_t*)output, sizeof(output), 100);

}

void Controller::LB(void)
{
	direction = CW;
	char direction[8] = "CW\r\n";
	HAL_UART_Transmit(&huart2, (uint8_t*)direction, sizeof(direction), 100);
}
void Controller::RB(void)
{
	direction = CCW;
	char direction[8] = "CCW\r\n";
	HAL_UART_Transmit(&huart2, (uint8_t*)direction, sizeof(direction), 100);

}
void Controller::LT(void)
{
	direction = BRAKE;
	char direction[8] = "BRAKE\r\n";
	HAL_UART_Transmit(&huart2, (uint8_t*)direction, sizeof(direction), 100);

}
void Controller::RT(void)
{
	direction = 0;
	char direction[8] = "FREE\r\n";
	HAL_UART_Transmit(&huart2, (uint8_t*)direction, sizeof(direction), 100);

}
void Controller::START(void)
{
	if( PID == true )
	{
		PID = false;
		char direction[10] = "NON_PID\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)direction, sizeof(direction), 100);

	}
	else
	{
		PID = true;
		char direction[8] = "PID\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)direction, sizeof(direction), 100);

	}
}
void Controller::BACK(void)
{
	V_output_pwm = 0;
	sprintf(output, "%d\r\n", V_output_pwm);
	HAL_UART_Transmit(&huart2, (uint8_t*)output, sizeof(output), 100);


	target_speed = 0;
	sprintf(output, "%d\r\n", target_speed);
	HAL_UART_Transmit(&huart2, (uint8_t*)output, sizeof(output), 100);

	PID = false;
	char direction[10] = "NON_PID\r\n";
	HAL_UART_Transmit(&huart2, (uint8_t*)direction, sizeof(direction), 100);

}

void Controller::LSU(void){}
void Controller::LSL(void){}
void Controller::LSR(void){}
void Controller::LSD(void){}

void Controller::CSU(void){}
void Controller::CSR(void){}
void Controller::CSL(void){}
void Controller::CSD(void){}

void Controller::RSU(void){}
void Controller::RSR(void){}
void Controller::RSL(void){}
void Controller::RSD(void){}*/


void Controller::footwork(uint8_t direction, uint16_t speed)
{
	uint8_t pwm = speed / 23.677;
	Function* function = new Function();
	if(direction == 1)
	{
		function -> drive_motor(1, 2, pwm, speed, true);
		function -> drive_motor(2, 2, pwm, speed, true);
		function -> drive_motor(3, 1, pwm, speed, true);
		function -> drive_motor(4, 1, pwm, speed, true);
	}
	else if(direction == 2)
	{
		function -> drive_motor(1, 2, pwm, speed, true);
		function -> drive_motor(2, 1, pwm, speed, true);
		function -> drive_motor(3, 1, pwm, speed, true);
		function -> drive_motor(4, 2, pwm, speed, true);
	}
	else if(direction == 3)
	{
		function -> drive_motor(1, 1, pwm, speed, true);
		function -> drive_motor(2, 1, pwm, speed, true);
		function -> drive_motor(3, 2, pwm, speed, true);
		function -> drive_motor(4, 2, pwm, speed, true);
	}
	else if(direction == 4)
	{
		function -> drive_motor(1, 1, pwm, speed, true);
		function -> drive_motor(2, 2, pwm, speed, true);
		function -> drive_motor(3, 2, pwm, speed, true);
		function -> drive_motor(4, 1, pwm, speed, true);
	}
	else if(direction == 5)
	{
		function -> drive_motor(1, 1, pwm, speed, true);
		function -> drive_motor(2, 1, pwm, speed, true);
		function -> drive_motor(3, 1, pwm, speed, true);
		function -> drive_motor(4, 1, pwm, speed, true);
	}
	else if(direction == 6)
	{
		function -> drive_motor(1, 2, pwm, speed, true);
		function -> drive_motor(2, 2, pwm, speed, true);
		function -> drive_motor(3, 2, pwm, speed, true);
		function -> drive_motor(4, 2, pwm, speed, true);
	}
	delete function;
}

void Controller::NOP(void)
{
	this -> speed = 700;
	Function* function = new Function();
	function -> drive_motor(1, 3, 0, 0, false);
	function -> drive_motor(2, 3, 0, 0, false);
	function -> drive_motor(3, 3, 0, 0, false);
	function -> drive_motor(4, 3, 0, 0, false);
	delete function;
}

void Controller::X(void){}
void Controller::Y(void){}
void Controller::A(void){}
void Controller::B(void){}

void Controller::LB(void)
{
	Init_Move* init_move = new Init_Move();
	init_move -> init_move(E_robot_name::A);
	delete init_move;
}

void Controller::RB(void){}
void Controller::LT(void){}
void Controller::RT(void){}
void Controller::START(void){}
void Controller::BACK(void){}


void Controller::LSU(void){}
void Controller::LSL(void){}
void Controller::LSR(void){}
void Controller::LSD(void){}

void Controller::CSU(void)
{
	this -> footwork(1, speed);

	this -> direction = 1;
}

void Controller::CSR(void)
{
	this -> footwork(2, speed);

	this -> direction = 2;
}

void Controller::CSL(void)
{
	this -> footwork(4, speed);

	this -> direction = 4;
}

void Controller::CSD(void)
{
	this -> footwork(3, speed);

	this -> direction = 3;
}

void Controller::RSU(void)
{
	this -> speed += 50;
	if(this -> speed >= 1000)
	{
		this -> speed = 1000;
	}
	this -> footwork(this -> direction, this -> speed);
}

void Controller::RSR(void)
{
	this -> footwork(5, 400);

	this -> direction = 5;
}
void Controller::RSL(void)
{
	this -> footwork(6, 400);

	this -> direction = 6;
}
void Controller::RSD(void)
{
	this -> speed -= 50;
	if(this -> speed <= 300)
	{
		this -> speed = 300;
	}
	this -> footwork(this -> direction, this -> speed);

}
