#include "ConnectStateManager.h"
#include "Connect.h"
#include "ConnectState.h"
#include "CanDropCheckerState.h"
#include "CantDropCheckerState.h"
#include "ResettingState.h"
#include "GameOverState.h"

ConnectStateManager::ConnectStateManager(Connect* newConnectGame) : currentState(NULL), connectGame(newConnectGame) {
    setState(getCanDropState());
}

void ConnectStateManager::onClick(int x, int y, PlayerManager* players, Board* board) {
    currentState->onClick(x, y, players, board);
}

void ConnectStateManager::onMouseMove(int x, int y, Board* board, Color& playersCurrentColor) {
    currentState->onMouseMove(x, y, board, playersCurrentColor);
}

void ConnectStateManager::update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board) {
    currentState->update(countdown, moveTimeLimit, switchPlayerTimeLimit, board);
}

void ConnectStateManager::draw(SpriteManager* sprites, Player* currentPlayer, PlayerIndicator* playerIndicator, Timer* countdown, const Position countdownPosition) {
    currentState->draw(sprites, currentPlayer, playerIndicator, countdown, countdownPosition);
}

bool ConnectStateManager::gameOver() const {
    return currentState->gameOver();
}

void ConnectStateManager::rotateTurns() {
   connectGame->rotateTurns();
}

void ConnectStateManager::setState(ConnectState* newState) {
    if (currentState) {
        delete currentState;
        currentState = NULL;
    }
    currentState = newState;
}

ConnectState* ConnectStateManager::getCanDropState() {
    return new CanDropCheckerState(this);
}

ConnectState* ConnectStateManager::getCantDropState() {
    return new CantDropCheckerState(this);
}

ConnectState* ConnectStateManager::getResettingState() {
    return new ResettingState(this);
}
ConnectState* ConnectStateManager::getGameOverState() {
    return new GameOverState(this);
}