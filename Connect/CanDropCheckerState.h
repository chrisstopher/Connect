#ifndef _CAN_DROP_CHECKER_STATE_H_
#define _CAN_DROP_CHECKER_STATE_H_

#include "ConnectState.h"

class CanDropCheckerState : public ConnectState {
public:
    CanDropCheckerState(ConnectStateManager* newStateManager);
    virtual void onClick(int x, int y, PlayerManager* players, Board* board);
    virtual void onMouseMove(int x, int y, Board* board, Color& playersCurrentColor);
    virtual void update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board);
    virtual void draw(SpriteManager* sprites, Player* currentPlayer, PlayerIndicator* playerIndicator, Timer* countdown, const Position countdownPosition);
private:
    
};

#endif