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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


uint8_t Controller::controller_Rxdata[8] = {128, 0, 0, 64, 64, 64, 64, 0};

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
//	this -> check_array();
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

	for( int i = 0; i < 8; i++ ) if( this -> controller_Rxdata[i] == initial_value[i] ) count++;

	if( count == 8 )
	{
		this -> NOP();
		char str[8] = "NOP\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);
		return true;
	}
	else return false;

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

	uint8_t data = 0;// 0 bit - left, 1 bit - right, 2 bit - down, 3 bit - up

	if( (this -> controller_Rxdata[2] & 0b00000001) == true) data |= ( true << 3 );//up
	else if( (this -> controller_Rxdata[2] & 0b00000010) >> 1 == true) data |= ( true << 2 );//down

	if( (this -> controller_Rxdata[2] & 0b00000100) >> 2 == true) data |= ( true << 1 );//right
	else if( (this -> controller_Rxdata[2] & 0b00001000) >> 3 == true) data |= ( true << 0 );//left

	switch( data )
	{
	case 0b00001001:
	{
		this -> LSUL();
		char str[8] = "LSUL\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00001010:
	{
		this -> LSUR();
		char str[8] = "LSUR\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;
	}
	case 0b00001000:
	{
		this -> LSU();
		char str[8] = "LSU\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000101:
	{
		this -> LSDL();
		char str[8] = "LSDL\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000110:
	{
		this -> LSDR();
		char str[8] = "LSDR\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000100:
	{
		this -> LSD();
		char str[8] = "LSD\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000001:
	{
		this -> LSL();
		char str[8] = "LSL\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;
	}
	case 0b00000010:
	{
		this -> LSR();
		char str[8] = "LSR\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;
	}

	}

}

void Controller::identify_RS()
{

	uint8_t data = 0;// 0 bit - left, 1 bit - right, 2 bit - down, 3 bit - up

	if( this -> controller_Rxdata[6] == 0b00000000 ) data |= ( true << 3 );//up
	else if( this -> controller_Rxdata[6] == 0b01111111 ) data |= ( true << 2 );//down

	if( this -> controller_Rxdata[5] == 0b01111111 ) data |= ( true << 1 );//right
	else if( this -> controller_Rxdata[5] == 0b00000000 ) data |= true;//left

	switch( data )
	{
	case 0b00001001:
	{
		this -> RSUL();
		char str[8] = "RSUL\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00001010:
	{
		this -> RSUR();
		char str[8] = "RSUR\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;
	}
	case 0b00001000:
	{
		this -> RSU();
		char str[8] = "RSU\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000101:
	{
		this -> RSDL();
		char str[8] = "RSDL\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000110:
	{
		this -> RSDR();
		char str[8] = "RSDR\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000100:
	{
		this -> RSD();
		char str[8] = "RSD\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000001:
	{
		this -> RSL();
		char str[8] = "RSL\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;
	}
	case 0b00000010:
	{
		this -> RSR();
		char str[8] = "RSR\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}

	}


}

void Controller::identify_CS()
{
	uint8_t data = 0;// 0 bit - left, 1 bit - right, 2 bit - down, 3 bit - up

	if( this -> controller_Rxdata[4] == 0b00000000 ) data |= ( true << 3 );//up
	else if( this -> controller_Rxdata[4] == 0b01111111 ) data |= ( true << 2 );//down

	if( this -> controller_Rxdata[3] == 0b01111111 ) data |= ( true << 1 );//right
	else if( this -> controller_Rxdata[3] == 0b00000000 ) data |= true;//left

	switch( data )
	{
	case 0b00001001:
	{
		this -> CSUL();
		char str[8] = "CSUL\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00001010:
	{
		this -> CSUR();
		char str[8] = "CSUR\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00001000:
	{
		this -> CSU();
		char str[8] = "CSU\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000101:
	{
		this -> CSDL();
		char str[8] = "CSDL\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000110:
	{
		this -> CSDR();
		char str[8] = "CSDR\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000100:
	{
		this -> CSD();
		char str[8] = "CSD\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000010:
	{
		this -> CSR();
		char str[8] = "CSR\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}
	case 0b00000001:
	{
		this -> CSL();
		char str[8] = "CSL\r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)str, sizeof(str), 100);

		break;

	}

	}

}





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
void Controller::LSUL(void){}
void Controller::LSUR(void){}
void Controller::LSDR(void){}
void Controller::LSDL(void){}


void Controller::CSU(void){}
void Controller::CSR(void){}
void Controller::CSL(void){}
void Controller::CSD(void){}
void Controller::CSUL(void){}
void Controller::CSUR(void){}
void Controller::CSDL(void){}
void Controller::CSDR(void){}

void Controller::RSUL(void){}
void Controller::RSU(void){}
void Controller::RSUR(void){}
void Controller::RSR(void){}
void Controller::RSDR(void){}
void Controller::RSD(void){}
void Controller::RSDL(void){}
void Controller::RSL(void){}



