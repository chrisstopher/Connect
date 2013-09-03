#ifndef _POSITION_H_
#define _POSITION_H_

#include <iostream>
class Position {
public:
	Position(int X = 0, int Y = 0);
	bool operator==(const Position& p) const;
	bool operator==(const int i) const;
	int x, y;
private:
	
};
bool operator!=(const Position& p1, const Position& p2);
bool operator!=(const Position& p, const int i);
std::ostream& operator<<(std::ostream& os, Position& p);
#endif