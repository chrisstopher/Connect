#ifndef _CONNECT_STATE_H_
#define _CONNECT_STATE_H_

#include "ConnectStateManager.h"

#include "SpriteManager.h"
#include "Timer.h"
#include "Board.h"
#include "PlayerIndicator.h"
#include "PlayerManager.h"

class ConnectState {
public:
    ConnectState(ConnectStateManager* newStateManager);
    virtual void onClick(int x, int y, PlayerManager* players, Board* board);
    virtual void onMouseMove(int x, int y, Board* board, Color& playersCurrentColor);
    virtual void update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board);
    virtual void draw(SpriteManager* sprites, Player* currentPlayer, PlayerIndicator* playerIndicator, Timer* countdown, const Position countdownPosition);
    virtual bool gameOver() const;

    void drawCountdown(SpriteManager* sprites, Color& color, Timer* countdown, const Position countdownPosition);
protected:
    ConnectStateManager* stateManager;
    
};

#endif