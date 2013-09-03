#include "Checker.h"

Checker::Checker(Position& startAt, Position& endAt, Color& newColor) : position(startAt), end(endAt), color(newColor) {
	
}

void Checker::drop() {
	position.y += DROP_SPEED;
	if (position.y > end.y) {
		position.y = end.y;
	}
}

bool Checker::atBottom() {
	return position.y == end.y;
}

Position& Checker::currentPosition() {
	return position;
}

Position& Checker::getEndingPosition() {
	return end;
}

Color& Checker::getColor() {
	return color;
}

void Checker::setAlpha(GLubyte a) {
	color.a = a;
}

void Checker::setEndingPosition(Position& endAt) {
	end = endAt;
}