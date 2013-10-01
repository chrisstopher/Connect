#include "CheckerManager.h"

CheckerManager::CheckerManager() : placingChecker(Position(), Position(), Color()), drawingPlacingChecker(false), fader(ALPHA_DEFAULT, 4, 0, ALPHA_DEFAULT, true, 0) {

}

CheckerManager::~CheckerManager() {
	clear();
}

void CheckerManager::add(Checker* checker) {
	checkers.push_back(checker);
}

/*
Updates each checker
If there are winning checkers indexes and the last checker has dropped into place
Fade the checkers at the indexes
*/
void CheckerManager::update() {
	unsigned i;
	for (i = 0; i < checkers.size(); i++) {
		checkers[i]->drop();
	}
	if (!winningCheckersIndexes.empty() && lastCheckerDropInPlace()) {
		fader.update();
		for (i = 0; i < winningCheckersIndexes.size(); i++) {
			checkers[winningCheckersIndexes[i]]->setAlpha(fader.getValue());
		}
	}
}

/*
Draws every checker
*/
void CheckerManager::draw(Sprite* sprite) {
	for (unsigned i = 0; i < checkers.size(); i++) {
		sprite->changeTextureColorAt(CHECKER_FRAME, checkers[i]->getColor());
		sprite->translateTo(checkers[i]->currentPosition());
		sprite->draw(0, 0, CHECKER_FRAME);
	}
	if (drawingPlacingChecker) {
		sprite->changeTextureColorAt(CHECKER_FRAME, placingChecker.getColor());
		sprite->translateTo(placingChecker.getEndingPosition());
		sprite->draw(0, 0, CHECKER_FRAME);
	}
	
}

/*
Clears the winning checkers indexes, resets the fader, and clears all checkers
*/
void CheckerManager::clear() {
	winningCheckersIndexes.clear();
	fader.setValue(ALPHA_DEFAULT);
	for (unsigned i = 0; i < checkers.size(); i++) {
		delete checkers[i];
	}
	checkers.clear();
}

bool CheckerManager::lastCheckerDropInPlace() {
	if (checkers.empty() || !checkers[checkers.size()-1]->atBottom()) {
		return false;
	}
	return true;
}

/*
After you reset or restart the game
It sets the ending positions of all the checkers to below the screen so they cannot be shown
And resets the alpha on all the winning checkers
*/
void CheckerManager::dropAllCheckers() {
	unsigned i;
	for (i = 0; i < checkers.size(); i++) {
		checkers[i]->setEndingPosition(Position(checkers[i]->currentPosition().x, SCREEN_WIDTH + SPRITE_HEIGHT));
	}
	for (i = 0; i < winningCheckersIndexes.size(); i++) {
		checkers[winningCheckersIndexes[i]]->setAlpha(ALPHA_DEFAULT);
	}
}

bool CheckerManager::fading() {
	return !winningCheckersIndexes.empty();
}

/*
Records the indexes of which checkers are the winning ones 
So it does not have to do this every frame, just once
*/
void CheckerManager::fadeTheCheckersAt(std::vector<Position>& positions) {
	winningCheckersIndexes.reserve(positions.size());
	for (unsigned i = 0; i < checkers.size(); i++) {
		for (unsigned j = 0; j < positions.size(); j++) {
			if (checkers[i]->currentPosition() == positions[j]) {
				winningCheckersIndexes.push_back(i);
			}
		}
	}
}

/*
Should only be called if there is atleast one checker dropped
*/
Position& CheckerManager::getLastCheckerDroppedPosition() {
	return checkers[checkers.size() - 1]->getEndingPosition();
}

unsigned int CheckerManager::size() const {
	return checkers.size();
}

void CheckerManager::setPlacingChecker(int x, int y, Color& color) {
	placingChecker.setColor(color);
	placingChecker.setEndingPosition(Position(x, y));
}

void CheckerManager::drawPlacingChecker() {
	drawingPlacingChecker = true;
}

void CheckerManager::dontDrawPlacingChecker() {
	drawingPlacingChecker = false;
}