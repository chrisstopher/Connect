#include "CantDropCheckerState.h"

CantDropCheckerState::CantDropCheckerState(ConnectStateManager* newStateManager)
: ConnectState(newStateManager) {
}

void CantDropCheckerState::update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board) {
    if (!countdown->lessThanOneSecondBeforeTimesUp()) {
		return;
	}
    stateManager->rotateTurns();
    stateManager->setState(stateManager->getCanDropState());
}

void CantDropCheckerState::draw(SpriteManager* sprites, Player* currentPlayer, PlayerIndicator* playerIndicator, Timer* countdown, const Position countdownPosition) {
    drawCountdown(sprites, Color(0, 0, 0), countdown, countdownPosition);
}