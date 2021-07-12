/*
 * Communication.cpp
 *
 *  Created on: 9 May 2021
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
#include "Communication.hpp"
#include "Error_Handling.hpp"
#include "Self_Pos.hpp"
#include "Jump.hpp"
#include "Gyro.hpp"

uint8_t Communication::Rxdata[4] = { 0, 0, 0, 0 };

void Communication::send_data(E_data_type data)
{

	switch(data)
	{
	case E_data_type::CURRENT_DATA:
	{
		Self_Pos* self_pos = new Self_Pos();
		Gyro* gyro = new Gyro();

		uint8_t X_pos_p = (uint8_t)(0b1111111100000000 & (uint16_t)self_pos -> get_Self_Pos_X()) >> 8;
		uint8_t X_pos_q = (uint8_t)(0b0000000011111111 & (uint16_t)self_pos -> get_Self_Pos_X());

		uint8_t Y_pos_p = (uint8_t)(0b1111111100000000 & (uint16_t)self_pos -> get_Self_Pos_Y()) >> 8;
		uint8_t Y_pos_q = (uint8_t)(0b0000000011111111 & (uint16_t)self_pos -> get_Self_Pos_Y());

		uint8_t direction_p = (uint8_t)(0b1111111100000000 & gyro -> get_direction()) >> 8;
		uint8_t direction_q = (uint8_t)(0b0000000011111111 & gyro -> get_direction());

		uint8_t current_line_p = (uint8_t)(0b1111111100000000 & (uint16_t)Error_Handling::current_line) >> 8;
		uint8_t current_line_q = (uint8_t)(0b0000000011111111 & (uint16_t)Error_Handling::current_line);

		Jump* jump = new Jump();

		uint8_t data[10] = { static_cast<uint8_t>(E_data_type::CURRENT_DATA), X_pos_p, X_pos_q, Y_pos_p, Y_pos_q, direction_p, direction_q, current_line_p, current_line_q, (uint8_t)jump -> get_status() };

		delete jump;

		HAL_UART_Transmit(&huart1, (uint8_t*)Error_Handling::current_func, sizeof(Error_Handling::current_func), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*)data, sizeof(data), 100);

		delete self_pos;
		delete gyro;

		break;
	}

	case E_data_type::WARNING_DATA:
	{
		uint8_t warning_line_p = (uint8_t)(0b1111111100000000 & (uint16_t)Error_Handling::warning_line) >> 8;
		uint8_t warning_line_q = (uint8_t)(0b0000000011111111 & (uint16_t)Error_Handling::warning_line);

		uint8_t data[3] = { static_cast<uint8_t>(E_data_type::WARNING_DATA), warning_line_p, warning_line_q };

		HAL_UART_Transmit(&huart1, (uint8_t*)Error_Handling::warning_func, sizeof(Error_Handling::warning_func), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*)data, sizeof(data), 100);

		break;

	}

	case E_data_type::ERROR_DATA:
	{
		uint8_t error_line_p = (uint8_t)(0b1111111100000000 & (uint16_t)Error_Handling::error_line) >> 8;
		uint8_t error_line_q = (uint8_t)(0b0000000011111111 & (uint16_t)Error_Handling::error_line);

		uint8_t data[3] = { static_cast<uint8_t>(E_data_type::ERROR_DATA), error_line_p, error_line_q };

		HAL_UART_Transmit(&huart1, (uint8_t*)Error_Handling::error_func, sizeof(Error_Handling::error_func), 100);
		HAL_UART_Transmit(&huart1, (uint8_t*)data, sizeof(data), 100);

		break;

	}
	case E_data_type::DONE_DATA:
	{

	}



	default:
		break;
	}




}
