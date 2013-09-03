#include "Position.h"

Position::Position(int X, int Y) : x(X), y(Y) {

}

bool Position::operator==(const Position& p) const {
	return (x == p.x && y == p.y);
}

bool Position::operator==(const int i) const {
	return (x == i && y == i);
}

bool operator!=(const Position& p1, const Position& p2) {
	return !(p1 == p2);
}

bool operator!=(const Position& p, const int i) {
	return !(p == i);
}

std::ostream& operator<<(std::ostream& os, Position& p) {
	os << p.x << ", " << p.y;
	return os;
}