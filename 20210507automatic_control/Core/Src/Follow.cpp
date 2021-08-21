/*
 * Follow.cpp
 *
 *  Created on: 4 Aug 2021
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
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "Follow.hpp"
#include "Self_Pos.hpp"
#include "Line.hpp"
#include "math.h"
#include "Path.hpp"


int16_t Follow::A_pos_x = -1200;
int16_t Follow::A_pos_y = -1200;

int Follow::target_X = 0;
int Follow::target_Y = 0;


void Follow::follow()
{
	Line* line = new Line();
	Self_Pos* self_pos = new Self_Pos();

	this -> target_calc();

	line -> Line_driver( self_pos -> get_Self_Pos_X(), self_pos -> get_Self_Pos_Y(), Follow::target_X, Follow::target_Y, false );

	delete line;
	delete self_pos;
}

void Follow::target_calc()
{

	Self_Pos* self_pos = new Self_Pos();


    int x_diff = Follow::A_pos_x - self_pos -> get_Self_Pos_X();
    int y_diff = Follow::A_pos_y - self_pos -> get_Self_Pos_Y();


    if( !( ( x_diff == 0 ) || ( y_diff == 0 ) ) )
    {
        double degree_B_to_A = atan( ( double )y_diff / ( double )x_diff );

        int target_x_1 = Follow::A_pos_x - FOLLOW_RADIUS * cos( degree_B_to_A );
        int target_y_1 = Follow::A_pos_y - FOLLOW_RADIUS * sin( degree_B_to_A );

        int target_x_2 = Follow::A_pos_x - FOLLOW_RADIUS * cos( degree_B_to_A + M_PI );
        int target_y_2 = Follow::A_pos_y - FOLLOW_RADIUS * sin( degree_B_to_A + M_PI );

        if( abs( target_x_1 - self_pos -> get_Self_Pos_X() ) < abs( target_x_2 - self_pos -> get_Self_Pos_X() ) )
        {
        	Follow::target_X = target_x_1;
        	Follow::target_Y = target_y_1;

        }
        else
        {

        	Follow::target_X = target_x_2;
        	Follow::target_Y = target_y_2;
        }


    }



	delete self_pos;

}
