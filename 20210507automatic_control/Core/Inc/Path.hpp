
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

#define SPEED_LIMIT 700
#define MIN_SPEED 500
#define TIME_NEEDED 1
#define MAX_ACCEL 50


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

};



#endif /* INC_PATH_HPP_ */
