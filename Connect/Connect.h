#ifndef _CONNECT_H_
#define _CONNECT_H_

#include "Constants.h"
#include "SpriteManager.h"
#include "Board.h"
#include "PlayerManager.h"
#include "Timer.h"
#include "NoTimer.h"
#include "PlayerIndicator.h"
#include "FileNames.h"

#include "ConnectStateManager.h"

class Connect {
public:
	Connect(int players, Timer* timer, int connectAmount, int rows, int columns);
	bool load();
	void onClick(int x, int y);
	void onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
	void logic();
	void draw();
	void free();
	void dropCheckers();
	void startOver();
	bool gameIsOver() const;
	bool allPlayersLastCheckerInPlace();
    void rotateTurns();
private:
	static const int BOARD = 0;
	const int PLAYER_COUNT;
	const int CONNECT_AMOUNT, ROWS, COLUMNS, MIN_ROWS, MIN_COLUMNS;
	static const int MAX_ROWS = 10, MAX_COLUMNS = 15;
	const int MOVE_TIME_LIMIT;
	static const int SWITCH_PLAYERS_TIME_LIMIT = 3;

	ConnectStateManager* connectStateManager;

	SpriteManager* sprites;
	Board* board;
	PlayerManager* players;
	Color boardColor;
	Timer* countdown;
	const Position COUNTDOWN_POSITION;
	PlayerIndicator* playerIndicator;
	static const int PLAYER_INDICATOR_FRAME = 2;
	static const int INDICATOR_X_OFFSET = 24;
	
};

#endif