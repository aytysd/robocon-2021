
/*
 * Path.hpp
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
#ifndef INC_PATH_HPP_
#define INC_PATH_HPP_

#include "main.h"

#define SPEED_LIMIT 500
#define MIN_SPEED 0
#define MAX_ACCEL 1

#define FR 600
#define TR 600

#define Kp 0.2
#define Ki 0.01
#define Kd 0.01

typedef struct
{
    double X = 0;
    double Y = 0;
}vector;

enum class E_path_status
{
	MOVING,
	STOP,
	REACHING,
};

class Path
{
public:
	void path_driver( int Ax, int Ay, int Bx, int By, bool through );
	void movepath( void );
	static E_path_status judge;

	static int16_t A_pos_x;
	static int16_t A_pos_y;

private:
	uint8_t where_target_is( double x, double y );
	double calc_t( vector A, vector B );
	double get_distance( vector A, vector B );


	static double Ax;
	static double Ay;
	static double Bx;
	static double By;

	static double direction;
	static double speed;

	static bool through;
	static bool arrive;

	double speed_PID( vector robot_A, vector self_pos );
	double P( vector robot_A, vector self_pos );
	double I( vector robot_A, vector self_pos );
	double D( vector robot_A, vector self_pos );

	static double integral_diff;

};



#endif /* INC_PATH_HPP_ */
