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
#include <cstring>
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


using namespace std;

template <>
void Debug::TTO_addr( uint16_t* var_address, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%d\r\n", *var_address );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );

}

template <>
void Debug::TTO_addr( uint32_t* var_address, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%d\r\n", *var_address );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );

}

template <>
void Debug::TTO_addr( uint8_t* var_address, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%d\r\n", *var_address );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );

}

template <>
void Debug::TTO_addr( int* var_address, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%d\r\n", *var_address );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );

}

template <>
void Debug::TTO_addr( int16_t* var_address, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%d\r\n", *var_address );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );

}


template <>
void Debug::TTO_addr( double* var_address, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%lf\r\n", *var_address );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );
}

template <>
void Debug::TTO_addr( float* var_address, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%lf\r\n", *var_address );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );

}


template< typename addr >
void Debug::TTO_addr( addr var_address, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%d\r\n", *var_address );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );
}



template<>
void Debug::TTO_val( int value, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%d\r\n", value );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );

}

template<>
void Debug::TTO_val( int16_t value, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%d\r\n", value );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );

}



template<>
void Debug::TTO_val( uint8_t value, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%d\r\n", value );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );
}

template<>
void Debug::TTO_val( uint16_t value, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%d\r\n", value );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );
}

template<>
void Debug::TTO_val( uint32_t value, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%d\r\n", value );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );
}

template<>
void Debug::TTO_val( double value, string str )
{

	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%lf\r\n", value );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );

}

template<>
void Debug::TTO_val( float value, string str )
{

	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;


	char output[ 10 ] = "0";

	sprintf( output, "%lf\r\n", value );
	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );
}






template< typename type >
void Debug::TTO_val( type value, string str )
{
	Debug* debug = new Debug();
	debug -> str_output( str );
	delete debug;

	char output[ sizeof( value ) + 1 ] = "0";
	sprintf( output, "%d\r\n", value );

	HAL_UART_Transmit( &huart2, (uint8_t*)output, sizeof( output ), 100 );
}



void Debug::time_calc(  )
{
	static int i;
	static uint32_t start_time;
	static uint32_t end_time;

	i++;


	switch( i % 2 )
	{
	case 1:
	{
		start_time = HAL_GetTick();
		Debug::TTO_addr( &start_time, "time calc starts:" );

		break;
	}
	case 0:
	{
		end_time = HAL_GetTick();
		uint32_t diff = end_time - start_time - 4;

		Debug::TTO_addr( &end_time, "time calc ends:" );
		Debug::TTO_addr( &diff, "diff:" );

		break;
	}

	}


}

void Debug::str_output( string str )
{

	int n = str.length();

	char array[ n + 1 ];
	std::strcpy( array, str.c_str() );
	HAL_UART_Transmit( &huart2, ( uint8_t* )array, sizeof( array ), 100 );

}


