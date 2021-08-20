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

#include "main.h"
#include "i2c.h"
#include "General_command.hpp"

class Line
{
private:
	int a;
	int b;
	int c;
	long double sqrtAABB;
	int now_X;
	int now_Y;
	double devX;
	double devY;
	long double devTG;
	long double TG_r;
	long double Line_r;
	long double dev_r;
	uint16_t now_r;
	uint16_t TG_v;

	void set(int befX, int befY, int tgX, int tgY);
	double distance(int x, int y, int tgX, int tgY);
	double TGdistance(int x, int y, int tgX, int tgY);

	static int AftX;
	static int AftY;
	static int BefX;
	static int BefY;
	static bool through;

public:
	void Line_driver(int bef, int befY, int tgX, int tgY, bool through);
	void MoveLine(void);
	static E_Line_status judge;

	static bool Enable_line;
};



#endif /* INC_LINE_HPP_ */
