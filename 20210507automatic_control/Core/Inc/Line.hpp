/*
 * Line.hpp
 *
 *  Created on: 2021/05/08
 *
 *@Author: nakakubo hiroto
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
#ifndef INC_LINE_HPP_
#define INC_LINE_HPP_

class Line
{
private:
	double a;
	double b;
	double c;
	double sqrtAABB;
	double r;
	double tg_X;
	double tg_Y;

public:
	void set(double befX, double befY, double tgX, double tgY);
	double distance(double x, double y);
	double TGdistance(double x, double y);
};



#endif /* INC_LINE_HPP_ */
