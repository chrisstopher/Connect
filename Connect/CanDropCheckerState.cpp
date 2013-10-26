#include "CanDropCheckerState.h"

CanDropCheckerState::CanDropCheckerState(ConnectStateManager* newStateManager)
: ConnectState(newStateManager) {

}

void CanDropCheckerState::onClick(int x, int y, PlayerManager* players, Board* board) {
    if (!board->isOver(x, y) || !board->columnIsNotFull(x)) {
		return;
	}
    bool gameOver = false;
	players->getCurrentPlayer()->dropChecker(x, board);			
	if (board->hasBeenWonBy(players->getCurrentPlayer())) {
		players->getCurrentPlayer()->increScore();
		gameOver = true;
	} else if (board->full()) {
		gameOver = true;
	}
	stateManager->rotateTurns();
	board->placeFadedChecker(x, y, players->getCurrentPlayer()->getColor());
    if (gameOver) {
        stateManager->setState(stateManager->getGameOverState());
    }
}

void CanDropCheckerState::onMouseMove(int x, int y, Board* board, Color& playersCurrentColor) {
    board->placeFadedChecker(x, y, playersCurrentColor);
}

void CanDropCheckerState::update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board) {
    if (!countdown->lessThanOneSecondBeforeTimesUp()) {
		return;
	}
    countdown->reset(switchPlayerTimeLimit);
    stateManager->setState(stateManager->getCantDropState());
}

void CanDropCheckerState::draw(SpriteManager* sprites, Player* currentPlayer, PlayerIndicator* playerIndicator, Timer* countdown, const Position countdownPosition) {
    drawCountdown(sprites, currentPlayer->getColor(), countdown, countdownPosition);
    playerIndicator->draw(sprites->at(SpriteManager::GAME_SPRITE));
}