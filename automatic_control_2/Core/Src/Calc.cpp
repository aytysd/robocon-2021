/*
 * p_m.cpp
 *
 *  Created on: 3 May 2021
 *      Author: Ayato Yoshida
 */

#include <Calc.hpp>
#include "main.h"

int Calc::plus_minus(double number)
{
	if( number > 0 )
	{
		return 1;
	}
	if( number < 0 )
	{
		return 2;
	}
	if( number == 0 )
	{
		return 3;
	}

}


