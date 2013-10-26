#ifndef _CANT_DROP_CHECKER_STATE_H_
#define _CANT_DROP_CHECKER_STATE_H_

#include "ConnectState.h"

class CantDropCheckerState : public ConnectState {
public:
    CantDropCheckerState(ConnectStateManager* newStateManager);
    virtual void update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board);
    virtual void draw(SpriteManager* sprites, Player* currentPlayer, PlayerIndicator* playerIndicator, Timer* countdown, const Position countdownPosition);
private:
    Color countdownColor;
};

#endif

