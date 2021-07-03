/*
 * Controller_MDC.cpp
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
