/*
 * Trans_Controller.cpp
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
#include <main.h>
#include "Trans_Controller.hpp"

void Trans_Controller::identify_start_button(){
	uint8_t start_button[8] = {128, 32, 0, 64, 64, 64, 64, 32};
	uint8_t count = 0;
	for(int i = 0; i<8; i++){
		if( Trans_Controller::controller_Rxdata[i] == start_button[i] ){
			count++;
		}

	}
	if(count == 8){
		Trans_Controller::status = true;
	}
}

void Trans_Controller::reset_status(void){
	Trans_Controller::status = false;
}

bool Trans_Controller::get_status(void){
	return Trans_Controller::status;
}

uint8_t Trans_Controller::controller_Rxdata[8] = {0};
bool Trans_Controller::status = false;

