/*
 * Jump.hpp
 *
 *  Created on: 9 May 2021
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
#ifndef INC_JUMP_HPP_
#define INC_JUMP_HPP_

#include "General_command.hpp"
#include "main.h"

//#define PE_Jump 1
//#define PE_Self_Pos 2
class Jump
{
public:

	void jump( void );
	void Jump_driver( E_Jump_status status );
	E_Jump_status get_Jump_status(void);
	void Into_Rope(void);
//	void PE_Sensor( int PE_num );
//	bool get_PE_status( int func );

	bool Is_centre( void );

	void RS_calc( void );

	static int rope;

private:
	static int16_t RS_0_90; //PC0
	static int16_t RS_90_180; //PC13
	static int16_t RS_180_270; //PA4
	static int16_t RS_270_0;
//	static bool PE_5;
//	void PE_init( void );

	int mode;
	int prev_mode;
	int count;

	static E_Jump_status Jump_status;
};



#endif /* INC_JUMP_HPP_ */
