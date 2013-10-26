#include "GameOverState.h"

GameOverState::GameOverState(ConnectStateManager* newStateManager)
: ConnectState(newStateManager) {
}

void GameOverState::update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board) {
    board->dontDrawFadedChecker();//only needs to be called once...
}

bool GameOverState::gameOver() const {
    return true;
}