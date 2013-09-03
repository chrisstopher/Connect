#include "PlayerIndicator.h"

PlayerIndicator::PlayerIndicator(unsigned newFrame, float newX, float newY, float Amount, float Min, float Max, bool Oscillate, float seconds, Color& newColor)
				: frame(newFrame), x(newX), y(newY, Amount, Min, Max, Oscillate, seconds), color(newColor) {
}

void PlayerIndicator::update() {
	y.update();
}

float PlayerIndicator::getX() const {
	return x;
}

float PlayerIndicator::getY() const {
	return y.getValue();
}

void PlayerIndicator::setX(float newX) {
	x = newX;
}

void PlayerIndicator::draw(Sprite* sprite) {
	sprite->changeTextureColorAt(frame, color);
	sprite->start();
	sprite->translateTo(x, y.getValue());
	sprite->draw(0, 0, frame);
	sprite->end();
}