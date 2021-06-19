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
#ifndef INC_CONTROLLER_HPP_
#define INC_CONTROLLER_HPP_

#include "main.h"
#include "General_command.hpp"
#include "PWM.hpp"

class Controller{
public:
	static uint8_t controller_Rxdata[8];
	void identify(void);


private:

	void check_array(void);

	void identify_ABXY_button(void);
	void identify_SUB_button(void);
	void identify_LS_SB(void);
	void identify_RS(void);
	void identify_CS(void);
	bool identify_NOP(void);

	void NOP(void);

	void X(void);
	void Y(void);
	void A(void);
	void B(void);

	void LB(void);
	void RB(void);
	void LT(void);
	void RT(void);
	void START(void);
	void BACK(void);

	void LSU(void);
	void LSL(void);
	void LSR(void);
	void LSD(void);

	void CSU(void);
	void CSR(void);
	void CSL(void);
	void CSD(void);

	void RSU(void);
	void RSR(void);
	void RSL(void);
	void RSD(void);


};



#endif /* INC_CONTROLLER_HPP_ */
