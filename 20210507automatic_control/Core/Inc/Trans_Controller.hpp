/*
 * Trans_Controller.hpp
 *
 *  Created on: May 9, 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(To know when "start button" of controller is pushed)
 *
 *
 *@Input(value)in(variable)of(functionname)
 *
 *@Output(whether "start button" is pushed (true or false))to(bool status)
 *
 *@Attention_(all of methods and variables in this class are static)
 *
 *@Usertouch(static void reset_status(void)
 *@Usertouch(static bool get_status(void))
 *
 */
#ifndef INC_TRANS_CONTROLLER_HPP_
#define INC_TRANS_CONTROLLER_HPP_

#include "main.h"
#include "General_command.hpp"
#include "PWM.hpp"

class Trans_Controller{
public:
	static uint8_t controller_Rxdata[8];

	void identify_start_button(void);
	void identify_stop_button(void);

	void reset_status(void);
	E_move_status get_status(void);
private:
	static E_move_status status;
};



#endif /* INC_TRANS_CONTROLLER_HPP_ */
