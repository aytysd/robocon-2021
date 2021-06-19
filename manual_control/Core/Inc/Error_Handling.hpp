/*
 * Error_Handler.hpp
 *
 *  Created on: Jun 5, 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(Handling error occurence)
 *
 *@Input(error type)in(E_errors errors)of(void set_flag(E_errors errors)
 *
 *@Output(latest executed line)to(uint32_t current_line)
 *@Output(latest executed function)to(char* current_func)
 *@Output(latest warning line)to(uint32_t warning_line)
 *@Output(latest warning function)to(char* warning_func)
 *@Output(error line)to(uint32_t error_line)
 *@Output(error func)to(const char* error_func)
 *@Output(error flag corresponding to E_Errors components)to(bool flag)
 *
 *@Attention_(only aytysd uses this class)
 *
 *
 */
#ifndef INC_ERROR_HANDLING_HPP_
#define INC_ERROR_HANDLING_HPP_

#include "main.h"

enum class E_Errors
{
	Init_move_failed,
	Initialization_failed,
	W_X_Encoder_Disconnection,
	W_Y_Encoder_Disconnection,
	W_gyro_Disconnection,
	Count,
};


class Error_Handling
{
public:
	void Emergency_stop(void);
	void set_flag(E_Errors errors);

	void TIM5_error_handling(void);
	void TIM2_error_handling(void);

	void gyro_error_handling(uint16_t direction);

	static const char* error_func;
	static uint32_t error_line;

	static char* warning_func;
	static uint32_t warning_line;

	static uint32_t current_line;
	static char* current_func;
private:
	static bool flag[static_cast<int>(E_Errors::Count) + 1 ];
};





#endif /* INC_ERROR_HANDLING_HPP_ */
