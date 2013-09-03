#ifndef _COUNTER_H_
#define _COUNTER_H_

#include "Sprite.h"

#include "Position.h"

class Counter {
public:
	Counter(int i = 0);
	Counter(int i, Position& newPosition);
	void set(int i);
	void incre(int i = 1);
	int getCount() const;
	int digitCount() const;
	void setX(int x);
	void setY(int y);
	Position& getPosition();
	void draw(Sprite* sprite, Color& color);
private:
	int count;
	Position position;
};

#endif