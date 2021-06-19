/*
 * Line.hpp
 *
 *  Created on: 2021/05/08
 *
 *@Author: nakakubo hiroto
 *
 *
 *@Purpose_of_this_class:(get the output along the target line)
 *
 *
 *@Input(before target X)in(befX)of(MoveLine)
 *@Input(before target Y)in(befY)of(MoveLine)
 *@Input(target X)in(tgX)of(set & MoveLine)
 *@Input(target Y)in(tgX)of(set & MoveLine)
 *
 *@Input(if a robot through the target pint)in(through)of(MoveLine)
 *
 *
 *@Output(the result(0~2(0:must move, 1:stopped, 2:through the target point))to(MoveLine)
 *
 *
 *@Attention_(When you used "MoveLine",
 *            if MoveLine returns 0, you can use "MoveLine" again.
 *            if MoveLine returns 1, a robot is stopped and can do other movement.
 *            if MoveLine returns 2, a robot is pass the target point and must move the next target pint.)
 *
 *@Attention_(MoveLine returns 2 only when "bool through" is "true".)
 *
 *
 *@Usertouch(MoveLine)&_(befX)
 *@Usertouch(MoveLine)&_(befY)
 *@Usertouch(MoveLine)&_(tgX)
 *@Usertouch(MoveLine)&_(tgY)
 *@Usertouch(MoveLine)&_(through)
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
	double now_X;
	double now_Y;
	double devX;
	double devY;
	double devTG;
	double TG_r;
	double now_r;
	int judge;


	void set(double befX, double befY, double tgX, double tgY);
	double distance(double x, double y, double tgX, double tgY);
	double TGdistance(double x, double y, double tgX, double tgY);


public:
	int MoveLine
	(double befX, double befY, double tgX, double tgY, bool through);
};



#endif /* INC_LINE_HPP_ */
