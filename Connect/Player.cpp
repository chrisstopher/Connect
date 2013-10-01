#include "Player.h"

Player::Player(int id, Color& newColor, Position& fontPosition)
	   : ID(id),
		 color(newColor),
		 score(0, fontPosition),
		 frame(1) {

}

Player::~Player() {
	
}

/*
converts the mouse's x position to the position of the grid that you clicked
*/
int Player::convertToGridPosition(int x, int boardX) {
	x -= boardX;
	x /= SPRITE_WIDTH;
	x *= SPRITE_WIDTH;
	x += boardX;
	return x;
}

/*
converts the mouse's x position to the position of the grid that you clicked in top left
then adds it to the board above the screen and sets the ending position and color
*/
void Player::dropChecker(int mouseX, Board* board) {
	mouseX = convertToGridPosition(mouseX, board->startingPosition().x);
	board->add(new Checker(Position(mouseX, -SPRITE_HEIGHT), board->getEndingPosition(mouseX), color), ID);
}

/*
Draws the players scores
*/
void Player::draw(Sprite* numberFont) {
	numberFont->start();
	score.draw(numberFont, color);
	numberFont->end();
}

int Player::getID() const {
	return ID;
}

void Player::increScore(int i) {
	score.incre(i);
}

void Player::setScoreToZero() {
	score.set(0);
}

Position& Player::getFontPosition() {
	return score.getPosition();
}

Color& Player::getColor() {
	return color;
}