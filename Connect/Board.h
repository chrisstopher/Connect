#ifndef _BOARD_H_
#define _BOARD_H_

#include "Globals.h"
#include "Position.h"
#include "Dynamic2dArray.h"
#include "CheckerManager.h"
#include "Sprite.h"
#include <algorithm>

class Player;

class Board {
public:
	Board(int connect, int rows, int columns, int id, Color& newColor, Position& startingPosition);
	~Board();
	bool isOver(int x, int y);
	bool columnIsNotFull(int x);
	Position& getEndingPosition(int x);
	bool full();
	void add(Checker* checker, int type);
	void update();
	bool hasBeenWonBy(Player* player);
	void draw(Sprite* sprite);
	void reset();
	Position& startingPosition();
	void dropAllCheckers();
	bool lastCheckerFullyDropped();

	void placeFadedChecker(int x, int y, Color& color, bool gameOver);
private:
	enum { NO_CHECKER = 0 };
	Dynamic2dArray<int> grid;
	Dynamic2dArray<Position> position;
	int connectCount, frame;
	Color color;
	CheckerManager checkers;
	std::vector<Position> winningCheckersPositions;
	int convertToColumnIndex(int i);
	int convertToRowIndex(int i);

	bool columnhasNoCheckers(int x);

	bool testsTheColumn(int column, int row, int playerId);
		bool testsTheColumnForConnectCount(int startAt, int whichColumn, int playerId);//do not need count here because not possible to have more than the count vertically connected

	bool testsTheRow(int column, int row, int playerId);
		bool testsTheRowAt(int columnToStartAt, int row, int howManyLoops, int count, int playerId);
			bool testsForAnAmountInRow(int count, int startAt, int whichRow, int playerId);

	bool testsNorthWestToSouthEastLeftSide(int column, int row, int playerId);
		bool testsNorthWestToSouthEastLeftSideStartingAt(int startAt, int column, int howManyToConnect, int playerId);
	bool testsNorthWestToSouthEastTopSide(int column, int row, int playerId);
		bool testsNorthWestToSouthEastTopSideStartingAt(int startAt, int row, int howManyToConnect, int playerId);
			bool testsNorthWestToSouthEast(int count, Position& startAt, int playerId);

	bool testsNorthEastToSouthWestTopSide(int column, int row, int playerId);
		bool testsNorthEastToSouthWestTopSideStartingAt(int startAt, int column, int howManyToConnect, int playerId);
	bool testsNorthEastToSouthWestRightSide(int column, int row, int playerId);
		bool testsNorthEastToSouthWestRightSideStartingAt(int startAt, int column, int howManyToConnect, int playerId);
			bool testsNorthEastToSouthWest(int count, Position& startAt, int playerId);
};

#endif