/*
 * Control.cpp
 *
 *  Created on: 9 Jul 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(description_about_thisclass)
 *
 *@Input(value)in(variable)of(functionname)
 *
 *@Output(value)to(where)
 *
 *@Attention_(uint8_t Control::master_Rxdata[0] = Flow_command
 *											[1] =
 *@Usertouch(functionname)&_(variable_name)
 *
 */

#include "Control.hpp"
#include "main.h"
#include "General_command.hpp"
#include "Init_Move.hpp"
#include "Line.hpp"
#include "Infinity_command.hpp"
#include "Self_Pos.hpp"

uint8_t Control::master_Rxdata[4] = { 0, 0, 0, 0 };

void Control::control ( E_robot_name robot )
{

	switch( robot )
	{
	case E_robot_name::A:
	{
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MOVE_INFINITY_INITIAL_POS )
		{
			Line* line = new Line();
			Self_Pos* self_pos = new Self_Pos();

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, true );
			while( Line::judge == E_Line_status::MOVING ){};

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, false );
			while( Line::judge == E_Line_status::MOVING ){};


			delete line;
			delete self_pos;
		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MODE_INFINITY_JUMP )
		{


		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MODE_SELF_POS_COR )
		{
			Line* line = new Line();
			Self_Pos* self_pos = new Self_Pos();

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};


			delete line;
			delete self_pos;


		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MOVE_DOUBLE_JUMP_INITIAL_POS )
		{
			Line* line = new Line();
			Self_Pos* self_pos = new Self_Pos();

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};


			delete line;
			delete self_pos;

		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MODE_DOUBLE_JUMP )
		{

		}

		break;
	}
	case E_robot_name::B:
	{
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MOVE_INFINITY_INITIAL_POS )
		{
			Line* line = new Line();
			Self_Pos* self_pos = new Self_Pos();

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};


			delete line;
			delete self_pos;
		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MODE_INFINITY_JUMP )
		{

		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MODE_SELF_POS_COR )
		{
			Line* line = new Line();
			Self_Pos* self_pos = new Self_Pos();

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};


			delete line;
			delete self_pos;


		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MOVE_DOUBLE_JUMP_INITIAL_POS )
		{
			Line* line = new Line();
			Self_Pos* self_pos = new Self_Pos();

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};


			delete line;
			delete self_pos;

		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MODE_DOUBLE_JUMP )
		{

		}

		break;
	}
	case E_robot_name::C:
	{
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MOVE_INFINITY_INITIAL_POS )
		{
			Line* line = new Line();
			Self_Pos* self_pos = new Self_Pos();

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};


			delete line;
			delete self_pos;
		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MODE_INFINITY_JUMP )
		{

		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MODE_SELF_POS_COR )
		{
			Line* line = new Line();
			Self_Pos* self_pos = new Self_Pos();

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};


			delete line;
			delete self_pos;


		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MOVE_DOUBLE_JUMP_INITIAL_POS )
		{
			Line* line = new Line();
			Self_Pos* self_pos = new Self_Pos();

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};

			line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), ( int )Infinity::A_Pos::START, ( int )Infinity::A_Pos::FINISH, true );
			while( Line::judge == E_Line_status::MOVING ){};


			delete line;
			delete self_pos;

		}
		if( Control::master_Rxdata[0] == (uint8_t)E_Flow::MODE_DOUBLE_JUMP )
		{

		}

		break;
	}
	}







}

