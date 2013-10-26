#ifndef _GAME_OVER_STATE_H_
#define _GAME_OVER_STATE_H_

#include "ConnectState.h"

class GameOverState : public ConnectState {
public:
    GameOverState(ConnectStateManager* newStateManager);
    virtual void update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board);
    virtual bool gameOver() const;
private:
};

#endif