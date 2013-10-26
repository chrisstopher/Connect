#include "ConnectState.h"

//#include "ConnectStateManager.h"

ConnectState::ConnectState(ConnectStateManager* newStateManager) : stateManager(newStateManager) {
    
}

void ConnectState::onClick(int x, int y, PlayerManager* players, Board* board) {

}

void ConnectState::onMouseMove(int x, int y, Board* board, Color& playersCurrentColor) {

}

void ConnectState::update(Timer* countdown, const unsigned moveTimeLimit, const unsigned switchPlayerTimeLimit, Board* board) {

}

void ConnectState::draw(SpriteManager* sprites, Player* currentPlayer, PlayerIndicator* playerIndicator, Timer* countdown, const Position countdownPosition) {

}

bool ConnectState::gameOver() const {
    return false;
}

void ConnectState::drawCountdown(SpriteManager* sprites, Color& color, Timer* countdown, const Position countdownPosition) {
    if (countdown->isRunning()) {
        sprites->at(SpriteManager::FONT_SPRITE)->start();
		sprites->at(SpriteManager::FONT_SPRITE)->translateTo(countdownPosition.x, countdownPosition.y);
		int frame = (countdown->seconds() < 1 ? 1 : countdown->seconds());
		sprites->at(SpriteManager::FONT_SPRITE)->changeTextureColorAt(frame, color);
		sprites->at(SpriteManager::FONT_SPRITE)->draw(0, 0, frame);
		sprites->at(SpriteManager::FONT_SPRITE)->end();
	}
}
