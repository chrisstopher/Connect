#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include "Checker.h"
#include "Sprite.h"
#include "Board.h"
#include "Counter.h"

class Player {
public:
	Player(int id, Color& newColor, Position& fontPosition);
	~Player();
	void dropChecker(int mouseX, Board* board);
	void logic();
	void draw(Sprite* numberFont);
	int getID() const;
	void addWinningChecker(Position& p);
	void printWinningCheckers();
	bool isWinningChecker(Checker* checker);
	bool lastCheckerDropInPlace();
	void reset();
	void dropAllCheckers();
	void increScore(int i = 1);
	void setScoreToZero();
	Position& getFontPosition();
	Color& getColor();
private:
	int ID;
	Color color;
	Counter score;
	int frame;
	int convertToGridPosition(int x, int boardX);
};

#endif