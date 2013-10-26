#ifndef _RESETTING_GAME_H_
#define _RESETTING_GAME_H_

#include "ConnectState.h"

class ResettingState : public ConnectState {
public:
    ResettingState(ConnectStateManager* newStateManager);
    virtual void update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board);
private:
};

#endif