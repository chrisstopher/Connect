#ifndef _CHECKER_H_
#define _CHECKER_H_

#include "Position.h"
#include "Sprite.h"

class Checker {
public:
	Checker(Position& startAt, Position& endAt, Color& newColor);
	void drop();
	bool atBottom();
	Position& currentPosition();
	Position& getEndingPosition();
	Color& getColor();
	void setAlpha(GLubyte a);
	void setEndingPosition(Position& endAt);
private:
	static const int DROP_SPEED = 10;
	Position position, end;
	Color color;
};

#endif