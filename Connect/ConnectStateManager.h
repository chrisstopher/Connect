#ifndef _CONNECT_STATE_MANAGER_H_
#define _CONNECT_STATE_MANAGER_H_

class Connect;
class ConnectState;

#include "SpriteManager.h"
#include "Timer.h"
#include "Board.h"
#include "PlayerIndicator.h"
#include "PlayerManager.h"

class ConnectStateManager {
public:
    ConnectStateManager(Connect* newConnectGame);

    void onClick(int x, int y, PlayerManager* players, Board* board);
    void onMouseMove(int x, int y, Board* board, Color& playersCurrentColor);
    void update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board);
    void draw(SpriteManager* sprites, Player* currentPlayer, PlayerIndicator* playerIndicator, Timer* countdown, const Position countdownPosition);
    bool gameOver() const;

    void rotateTurns();

    void setState(ConnectState* newState);
    ConnectState* getCanDropState();
    ConnectState* getCantDropState();
    ConnectState* getResettingState();
    ConnectState* getGameOverState();
private:
    ConnectState* currentState;
    Connect* connectGame;
};

#endif