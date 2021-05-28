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

void Controller::identify_start_button(){
	uint8_t start_button[8] = {128, 32, 0, 64, 64, 64, 64, 32};
	uint8_t count = 0;
	for(int i = 0; i<8; i++){
		if( Controller::controller_Rxdata[i] == start_button[i] ){
			count++;
		}

	}
	if(count == 8){
		Controller::status = E_move_status::MOVE;
	}
}

void Controller::identify_stop_button(){
	uint8_t stop_button[8] = {128, 64, 0, 64, 64, 64, 64, 64};
	uint8_t count = 0;
	for(int i = 0; i<8; i++){
		if( Controller::controller_Rxdata[i] == stop_button[i] ){
			count++;
		}

	}
	if(count == 8){
		Controller::status = E_move_status::STOP;
		HAL_UART_Transmit(&huart1, (uint8_t*)E_move_status::STOP, sizeof(E_move_status::STOP), 100);
		Function* function = new Function();
		for(int i = 0; i<8; i++){

			function -> drive_motor(i, 0, 0);
		}
		Error_Handler();
	}

}

void Controller::reset_status(void){
	Controller::status = E_move_status::FREE;
}

E_move_status Controller::get_status(void){
	return Controller::status;
}

uint8_t Controller::controller_Rxdata[8] = {0};
E_move_status Controller::status = E_move_status::FREE;

