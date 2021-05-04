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
		return CW;
	}
	if( number < 0 )
	{
		return CCW;
	}
	if( number == 0 )
	{
		return BRAKE;
	}

}


