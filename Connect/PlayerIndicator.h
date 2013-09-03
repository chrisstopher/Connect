#ifndef _PLAYERINDICATOR_H_
#define _PLAYERINDICATOR_H_

#include "Oscillator.h"

class PlayerIndicator {
public:
	PlayerIndicator(unsigned newFrame, float newX, float newY, float Amount, float Min, float Max, bool Oscillate, float seconds, Color& newColor);
	void update();
	float getX() const;
	float getY() const;
	void setX(float newX);
	void draw(Sprite* sprite);
private:
	unsigned frame;
	float x;
	Oscillator y;
	Color color;
};

#endif