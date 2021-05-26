/*
 * Wait.cpp
 *
 *  Created on: 27 May 2021
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
#include "Wait.hpp"
#include <iostream>

using namespace std;

bool Wait::wait( bool condition ){

	while( condition == false ){

		cout << "wait young lady, he said" << endl;
		HAL_Delay(1000);

	}
}

