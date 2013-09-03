#include "Counter.h"

Counter::Counter(int i) : count(i) {
	
}

Counter::Counter(int i, Position& newPosition) : count(i), position(newPosition) {
	
}

void Counter::set(int i) {
	count = i;
}

void Counter::incre(int i) {
	count += i;
}

int Counter::getCount() const {
	return count;
}

int Counter::digitCount() const {
	return (count < 10 ? 1 :
			count < 100 ? 2 :
			count < 1000 ? 3 :
			count < 10000 ? 4 :
			count < 100000 ? 5 :
			count < 1000000 ? 6 :
			count < 10000000 ? 7 :
			count < 100000000 ? 8 :
			count < 1000000000 ? 9 : 10);
}

void Counter::setX(int x) {
	position.x = x;
}

void Counter::setY(int y) {
	position.y = y;
}

Position& Counter::getPosition() {
	return position;
}

void Counter::draw(Sprite* sprite, Color& color) {
	int digits = digitCount();
	int tensDigit = getCount();
	for (int i = 0; i < digits; i++) {
		sprite->translateTo(position.x + ((sprite->getSpriteWidth() / 2 * (digits-2)) - sprite->getSpriteWidth() * i), position.y);
		sprite->changeTextureColorAt(tensDigit % 10, color);
		sprite->draw(0 - (digits - 1) * sprite->getSpriteWidth() / 2, 0, tensDigit % 10);
		tensDigit /= 10;
	}
}