/*
 * Trans_Controller.hpp
 *
 *  Created on: May 9, 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:( identify the button which you pushed, and implement some treatment )
 *
 *
 *@Input(value)in(variable)of(functionname)
 *
 *@Output( call a function corresponding to button or stick )
 *
 *@Attention_(  A() -> A button
				B() -> B button

				LSU() -> Left_Stick_Up
				LSR() -> Left_Stick_Right

				CSD() -> Cross_Stick_Down
				CSL() -> Cross_Stick_Left

				RSR() -> Right_Stick_Right
				RSU() -> Right_Stick_Up

				NOP() -> status which you aren't pushing any buttons

				START() -> Start_button
				BACK() -> BACK_button


				)


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
#include "Init_Move.hpp"


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


//	uint16_t speed;
//	uint8_t direction;/*1=up, 2=right, 3=down, 4=left, 5=R_turn, 6=L_turn*/
	void footwork(uint8_t direction, uint16_t speed);

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
	void LSUL(void);
	void LSUR(void);
	void LSDR(void);
	void LSDL(void);


	void CSU(void);
	void CSR(void);
	void CSL(void);
	void CSD(void);
	void CSUL(void);
	void CSUR(void);
	void CSDL(void);
	void CSDR(void);


	void RSU(void);
	void RSR(void);
	void RSL(void);
	void RSD(void);
	void RSUL(void);
	void RSUR(void);
	void RSDR(void);
	void RSDL(void);
};



#endif /* INC_CONTROLLER_HPP_ */
