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
 *@Input(before target X)in(befX)of(set & MoveLine)
 *@Input(before target Y)in(befY)of(set & MoveLine)
 *@Input(target X)in(tgX)of(set & MoveLine)
 *@Input(target Y)in(tgX)of(set & MoveLine)
 *
 *@Input(now X)in(x)of(distance & TGdistance & MoveLine)
 *@Input(now Y)in(y)of(distance & TGdistamce & MoveLine)
 *
 *@Input(if a robot through the target pint)in(through)of(MoveLine)
 *
 *
 *@Output(the value of the distance between a robot and the target line)to(double distance)
 *@Output(the value of the horizontal distance from the robot to the target pint)to(double TGdisatace)
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
 *@Usertouch(MoveLine)&_(x)
 *@Usertouch(MoveLine)&_(Y)
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
	double r;
	double tg_X;
	double tg_Y;
	double devX;
	double devY;
	double devTG;
	double TG_r;
	double now_r;
	int judge;

public:
	Line();
	void set(double befX, double befY, double tgX, double tgY);
	double distance(double x, double y);
	double TGdistance(double x, double y);
	int MoveLine
	(double befX, double befY, double tgX, double tgY,double x, double y, bool throug);
};



#endif /* INC_LINE_HPP_ */
