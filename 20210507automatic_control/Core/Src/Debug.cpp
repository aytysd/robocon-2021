/*
 * Debug.cpp
 *
 *  Created on: 17 Jul 2021
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
#include "Debug.hpp"
#include "stdio.h"
#include "main.h"
#include "string.h"
#include <string>


template <>
void Debug::TTO_addr( uint16_t* var_address, const char* str, UART_HandleTypeDef* UART )
{
	char output[13] = "0";

	sprintf( output, "%d\r\n", *var_address );
	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );

}

template <>
void Debug::TTO_addr( uint32_t* var_address, const char* str, UART_HandleTypeDef* UART )
{
	char output[13] = "0";

	sprintf( output, "%d\r\n", *var_address );
	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );

}

template <>
void Debug::TTO_addr( uint8_t* var_address, const char* str, UART_HandleTypeDef* UART )
{
	char output[13] = "0";

	sprintf( output, "%d\r\n", *var_address );
	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );

}

template <>
void Debug::TTO_addr( int* var_address, const char* str, UART_HandleTypeDef* UART )
{
	char output[13] = "0";

	sprintf( output, "%d\r\n", *var_address );
	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );

}

template <>
void Debug::TTO_addr( double* var_address, const char* str, UART_HandleTypeDef* UART )
{
	char output[13] = "0";

	sprintf( output, "%lf\r\n", *var_address );
	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );

}

template <>
void Debug::TTO_addr( float* var_address, const char* str, UART_HandleTypeDef* UART )
{
	char output[13] = "0";

	sprintf( output, "%lf\r\n", *var_address );
	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );

}


template< typename addr >
void Debug::TTO_addr( addr var_address, const char* str, UART_HandleTypeDef* UART )
{
	char output[10] = "0";

	sprintf( output, "%d\r\n", *var_address );
	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );
}



template<>
void Debug::TTO_val( int value, const char* str, UART_HandleTypeDef* UART )
{
	char output[10] = "0";

	sprintf( output, "%d\r\n", value );

	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );

}


template<>
void Debug::TTO_val( uint8_t value, const char* str, UART_HandleTypeDef* UART )
{
	char output[10] = "0";

	sprintf( output, "%d\r\n", value );
	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );
}

template<>
void Debug::TTO_val( uint16_t value, const char* str, UART_HandleTypeDef* UART )
{
	char output[10] = "0";

	sprintf( output, "%d\r\n", value );
	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );
}

template<>
void Debug::TTO_val( uint32_t value, const char* str, UART_HandleTypeDef* UART )
{
	char output[10] = "0";

	sprintf( output, "%d\r\n", value );
	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );
}

template<>
void Debug::TTO_val( double value, const char* str, UART_HandleTypeDef* UART )
{
	char output[10] = "0";

	sprintf( output, "%lf\r\n", value );
	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );
}

template<>
void Debug::TTO_val( float value, const char* str, UART_HandleTypeDef* UART )
{
	char output[10] = "0";

	sprintf( output, "%lf\r\n", value );


	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );
}






template< typename type >
void Debug::TTO_val( type value, const char* str, UART_HandleTypeDef* UART )
{
	char output[10] = "0";

	sprintf( output, "%d\r\n", value );

	HAL_UART_Transmit( UART, (uint8_t*)str, sizeof( str ), 100 );
	HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );
}



void Debug::time_calc( UART_HandleTypeDef* UART )
{
	static int i;
	static uint32_t start_time;
	static uint32_t end_time;

	i++;


	switch( i % 2 )
	{
	case 1:
		start_time = HAL_GetTick();
		break;
	case 0:
	{
		end_time = HAL_GetTick();
		uint32_t diff = end_time - start_time;

		char output[10] = "0";
		char desc[10] = "Time";
		sprintf( output, "%d\r\n", diff );
		HAL_UART_Transmit( UART, (uint8_t*)desc, sizeof( desc ), 100 );
		HAL_UART_Transmit( UART, (uint8_t*)output, sizeof( output ), 100 );

		break;
	}

	}


}


