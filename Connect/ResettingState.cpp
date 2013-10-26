#include "ResettingState.h"

ResettingState::ResettingState(ConnectStateManager* newStateManager)
: ConnectState(newStateManager) {
}

void ResettingState::update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board) {
    if (!board->lastCheckerFullyDropped()) {
		return;
	}
	board->reset();
	countdown->reset(moveTimeLimit);
    stateManager->setState(stateManager->getCanDropState());
}