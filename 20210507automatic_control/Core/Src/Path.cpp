/*
 * Path.cpp
 *
 *  Created on: 10 Aug 2021
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



#include "math.h"
#include "stdio.h"
#include "stdio.h"
#include "Path.hpp"
#include "Self_Pos.hpp"
#include "PWM.hpp"
#include "Gyro.hpp"
#include "MPU6050.hpp"
#include "Debug.hpp"
#include "usart.h"
#include "i2c.h"
#include "float.h"

int16_t Path::A_pos_x = 2643;
int16_t Path::A_pos_y = 2643;

double Path::integral_diff = 0;

double Path::Ax = 0;
double Path::Ay = 0;
double Path::Bx = 0;
double Path::By = 0;

double Path::direction = 0;
double Path::speed = 0;

bool Path::arrive = false;
bool Path::through = false;

E_path_status Path::judge = E_path_status::MOVING;


void Path::path_driver( int Ax, int Ay, int Bx, int By, bool through )
{
	Path::Ax = Ax;
	Path::Ay = Ay;
	Path::Bx = Bx;
	Path::By = By;
	Path::through = through;
	Path::arrive = false;
}

void Path::movepath( void )
{

	PWM* pwm = new PWM();
	MPU6050* gyro = new MPU6050();


	vector robot_A;
	vector self_pos;

	vector A_pos;
	vector B_pos;

	vector MA_vector;
	vector MB_vector;
	vector MD_vector;
	vector target;

	robot_A.X = Path::A_pos_x;
	robot_A.Y = Path::A_pos_y;

	Self_Pos* sp = new Self_Pos();
	self_pos.X = sp -> get_Self_Pos_X();
	self_pos.Y = sp -> get_Self_Pos_Y();
	delete sp;


	A_pos.X = Path::Ax;
	A_pos.Y = Path::Ay;

	B_pos.X = Path::Bx;
	B_pos.Y = Path::By;


	MA_vector.X = A_pos.X - self_pos.X;
	MA_vector.Y = A_pos.Y - self_pos.Y;

	MB_vector.X = B_pos.X - self_pos.X;
	MB_vector.Y = B_pos.Y - self_pos.Y;

	MD_vector.X = MA_vector.X + this -> calc_t( MA_vector, MB_vector ) * ( MB_vector.X - MA_vector.X );
	MD_vector.Y = MA_vector.Y + this -> calc_t( MA_vector, MB_vector ) * ( MB_vector.Y - MA_vector.Y );

	target.X = ( MD_vector.X + MB_vector.X ) / 2;
	target.Y = ( MD_vector.Y + MB_vector.Y ) / 2;




	if( this -> get_distance( robot_A, self_pos ) <= FR )
	{
		PWM* pwm = new PWM();

		Path::speed = 0;
		pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );

		delete pwm;
	}
	else
	{
		if( this -> get_distance( B_pos, self_pos ) < TR )
		{
			Path::arrive = true;

			if( Path::through == true )
			{
				Path::speed = 500;
				pwm -> V_output( Path::speed, Path::direction, 0, gyro -> get_direction( &hi2c1 ), E_move_status::MOVE );
				Path::judge = E_path_status::REACHING;
				delete pwm;
				delete gyro;
				return;

			}
			else
			{
				Path::speed = 0;
				Path::judge = E_path_status::STOP;
				pwm -> V_output( 0, 0, 0, 0, E_move_status::STOP );
				delete pwm;
				delete gyro;
				return;
			}

		}
		else
		{
			double target_speed = this -> speed_PID( robot_A, self_pos );

			if( target_speed >= SPEED_LIMIT )
				target_speed = SPEED_LIMIT;


			if( target_speed > Path::speed )
				Path::speed += MAX_ACCEL;
			else
				Path::speed = target_speed;


			if( target.X == 0 )
				target.X = 0.1;

			Path::direction = atan( target.Y / target.X );
			Path::direction = 180 * ( Path::direction / M_PI );

			switch( this -> where_target_is( target.X, target.Y ) )
			{
			case 1:
			case 4:
				break;
			case 3:
			case 2:
				Path::direction += 180;
				break;

			}

			while( Path::direction <= 0 )
				Path::direction += 360;


			target.X += self_pos.X;
			target.Y += self_pos.Y;


			Path::speed = 300;
			pwm -> V_output( ( uint16_t )Path::speed, ( uint16_t )Path::direction, 0, ( uint16_t )gyro -> get_direction( &hi2c1 ), E_move_status::MOVE );

			Path::judge = E_path_status::MOVING;

/*
			Debug::TTO_val( ( int )target.X, "X:", &huart2 );
			Debug::TTO_val( ( int )target.Y, "Y:", &huart2 );
*/
			Debug::TTO_val( ( int )Path::direction, "direction:" );
//			Debug::TTO_val( ( uint16_t )Path::speed, "speed:", &huart2 );
//			Debug::TTO_val( ( int )target_speed, "target_speed", &huart2 );

		}

		delete gyro;
		delete pwm;

	}



}

double Path::calc_t( vector A, vector B )
{
    double t;

    if( B.X == A.X )
    	A.X += 1;
    if( B.Y == A.Y )
    	A.Y += 1;

    double upper = ( A.Y / ( A.X - B.X ) ) - ( A.X / ( B.Y - A.Y ) );
    double lower = ( ( B.X - A.X ) / ( B.Y - A.Y ) ) - ( ( B.Y - A.Y ) / ( A.X - B.X ) );

    t = upper / lower;

    return t;
}

uint8_t Path::where_target_is( double x, double y )
{

    if( x >= 0 )
    {
        if( y >= 0 )
            return 1;
        else
            return 4;
    }
    else
    {
        if( y >= 0 )
            return 2;
        else
            return 3;

    }

}

double Path::get_distance( vector A, vector B )
{

    double distance = sqrt( ( ( A.X - B.X ) *  ( A.X - B.X ) ) + ( ( A.Y - B.Y ) * ( A.Y - B.Y ) ) );
    return distance;

}

double Path::speed_PID( vector robot_A, vector self_pos )
{
	return this -> P( robot_A, self_pos ) + this -> I( robot_A, self_pos ) - this -> D( robot_A, self_pos );
}

double Path::P( vector robot_A, vector self_pos )
{
	return Kp * this -> get_distance( robot_A, self_pos );
}

double Path::I( vector robot_A, vector self_pos )
{

	if( Path::arrive == true )
	{
		Path::integral_diff = 0;
		return 0;
	}
	else
	{
		Path::integral_diff += this -> get_distance( robot_A, self_pos );
		return Ki * Path::integral_diff;
	}


}

double Path::D( vector robot_A, vector self_pos )
{
	static double prev_diff;

	double dev = this -> get_distance( robot_A, self_pos ) - prev_diff;
	prev_diff = this -> get_distance( robot_A, self_pos );

	return Kd * dev;

}
