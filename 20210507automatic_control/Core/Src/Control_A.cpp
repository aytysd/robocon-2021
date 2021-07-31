/*
 * Control_A.cpp
 *
 *  Created on: 1 Aug 2021
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

#include "Control.hpp"
#include "main.h"
#include "General_command.hpp"
#include "Init_Move.hpp"
#include "Line.hpp"
#include "Infinity_command.hpp"
#include "Self_Pos.hpp"
#include "Jump.hpp"
#include "LED.hpp"
#include "usart.h"



int Infinity::A_pos_X[ 6 ] = { -1200, 1200, 2400, 1200, -1200, -2400 };
int Infinity::A_pos_Y[ 6 ] = { -1200, 1200, 0, 1200, 1200, 0 };


void Control::control_A (void)
{

	if( C_data[0] == ( uint8_t )E_data_type::command )
	{

		Control::Is_busy = true;

		switch( C_data[1] )
		{
		case ( uint8_t )E_Flow::MOVE_INFINITY_INITIAL_POS:
		{
			Line* line = new Line();
			Self_Pos* self_pos = new Self_Pos();

			line -> Line_driver( -2643, 2643, ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, true );
			while( Line::judge == E_Line_status::MOVING ){};

			line -> Line_driver( ( int )Infinity::A_Pos::L_SPC_X, ( int )Infinity::A_Pos::L_SPC_Y, ( int )Infinity::A_Pos::LD_X, ( int )Infinity::A_Pos::LD_Y, false );
			while( Line::judge == E_Line_status::MOVING ){};

			uint8_t data[4] = { ( uint8_t )E_data_type::done, 0, 0, 0 };
			this -> send_command( E_robot_name::C, data );

			delete line;
			delete self_pos;

			break;

		}
		case ( uint8_t )E_Flow::MODE_INFINITY_JUMP:
		{
			Line* line = new Line();


			for( int count = 0; count < 18; count++ )
			{

				bool through = true;

				switch( ( count % 6 ) + 1 )
				{
				case 2:
				case 5:
					through = false;
					break;
				}

				line -> Line_driver( Infinity::A_pos_X[ count % 6 ], Infinity::A_pos_Y[ count % 6 ], Infinity::A_pos_X[ ( count % 6 ) + 1 ], Infinity::A_pos_Y[ ( count % 6 ) + 1 ], through );
				while( Line::judge == E_Line_status::MOVING )
				{

					if( ( ( count % 6 ) + 1 ) == 1 )
					{
						Jump* jump = new Jump();
						delete jump;
					}

				};

				switch( ( count % 6 ) + 1 )
				{
				case 2:
				case 5:
				{
					Self_Pos* self_pos = new Self_Pos();
					delete self_pos;
					break;
				}


				}

			}


			delete line;
			break;

		}
		case ( uint8_t )E_Flow::MOVE_DOUBLE_JUMP_INITIAL_POS:
		{
			Line* line = new Line();
			Self_Pos* self_pos = new Self_Pos();

			uint8_t data[4] = { ( uint8_t )E_data_type::done, 0, 0, 0 };
			this -> send_command( E_robot_name::C, data );

			delete line;
			delete self_pos;

			break;
		}
		case ( uint8_t )E_Flow::MODE_DOUBLE_JUMP:
		{
			break;
		}
		default:

			break;
		}

	}

	Control::Is_busy = false;

	for( int i = 0; i < sizeof( C_data ); i++ )
		C_data[ i ] = 0;


}

