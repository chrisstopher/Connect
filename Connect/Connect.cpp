#include "Connect.h"

Connect::Connect(int players, Timer* timer, int connectAmount, int rows, int columns)
	: PLAYER_COUNT(players),
	  CONNECT_AMOUNT(connectAmount),
	  ROWS(rows), COLUMNS(columns),
	  MIN_ROWS(connectAmount), MIN_COLUMNS(connectAmount),
	  MOVE_TIME_LIMIT(timer->getDelayInSeconds() > 0 ? timer->getDelayInSeconds() + 1 : 0),
	  sprites(NULL),
	  board(NULL),
	  players(NULL),
	  gameOver(false),
	  reset(false),
	  boardColor(0, 0, 0),
	  countdown(timer),
	  COUNTDOWN_POSITION(SCREEN_WIDTH / 2 - FONT_WIDTH / 2, 64),
	  canDropChecker(true),
	  playerIndicator(NULL) {

}

bool Connect::load() {
	if (CONNECT_AMOUNT < 2) {
		std::cout << "You must have atleast 2 to connect.\n";
		return false;
	} else if (CONNECT_AMOUNT > std::min(ROWS, COLUMNS)) {
		std::cout << "There can only be a maximum of " << std::min(ROWS, COLUMNS) << " to connect.\n";
		return false;
	}
	if (ROWS < MIN_ROWS || COLUMNS < MIN_COLUMNS) {
		std::cout << "There needs to be atleast " << MIN_ROWS << " rows and atleast " << MIN_COLUMNS << " columns.\n";
		return false;
	} else if (ROWS > MAX_ROWS || COLUMNS > MAX_COLUMNS) {
		std::cout << "There can only be a maximum of " << MAX_ROWS << " rows and a maximum of " << MAX_COLUMNS << " columns.\n";
		return false;
	}
	players = new PlayerManager();
	if (!players->load(PLAYER_COUNT)) {
		return false;
	}
	const int BOARD_OFFSET_Y = 24;
	board = new Board(CONNECT_AMOUNT, ROWS, COLUMNS, BOARD, boardColor, Position(SCREEN_WIDTH / 2 - COLUMNS * SPRITE_WIDTH / 2,
																				(SCREEN_HEIGHT / 2 - ROWS * SPRITE_HEIGHT / 2) + BOARD_OFFSET_Y));
	playerIndicator = new PlayerIndicator(PLAYER_INDICATOR_FRAME,
										  players->getCurrentPlayer()->getFontPosition().x - INDICATOR_X_OFFSET,
										  players->getCurrentPlayer()->getFontPosition().y,
										  1.0f,
										  players->getCurrentPlayer()->getFontPosition().y - 2.0f,
										  players->getCurrentPlayer()->getFontPosition().y + 4.0f,
										  true,
										  0.05f,
										  boardColor);
	sprites = new SpriteManager();
	if (!sprites->load(GAME_SPRITES_FILE)) {
		return false;
	}
	countdown->reset((float)MOVE_TIME_LIMIT);
	return true;
}

/*
Makes sure that the user can click and that it was a valid location
Then drop the checker
Check if the game has been won
Check if board is full
then Rotate turns
*/
void Connect::onClick(int mX, int mY) {
	if (gameOver || !canDropChecker || !board->isOver(mX, mY) || !board->columnIsNotFull(mX)) {
		return;
	}
	players->getCurrentPlayer()->dropChecker(mX, board);			
	if (board->hasBeenWonBy(players->getCurrentPlayer())) {
		players->getCurrentPlayer()->increScore();
		gameOver = true;
	} else if (board->full()) {
		gameOver = true;
	}
	rotateTurns();
}

void Connect::logic() {
	playerIndicator->update();
	board->update();
	resetGame();
	updateTimer();
}

/*
Draws the countdown if it is running
Draws every player
Draws the board
Draws the player indicator
*/
void Connect::draw() {
	if (!gameOver && countdown->isRunning()) {
		Color fontColor((!canDropChecker ? boardColor : players->getCurrentPlayer()->getColor()));
		sprites->at(FONT_SPRITE)->start();
		sprites->at(FONT_SPRITE)->translateTo(COUNTDOWN_POSITION.x, COUNTDOWN_POSITION.y);
		int frame = (countdown->seconds() < 1 ? 1 : countdown->seconds());
		sprites->at(FONT_SPRITE)->changeTextureColorAt(frame, fontColor);
		sprites->at(FONT_SPRITE)->draw(0, 0, frame);
		sprites->at(FONT_SPRITE)->end();
	}
	players->draw(sprites->at(FONT_SPRITE));
	board->draw(sprites->at(GAME_SPRITE));
	if (canDropChecker && !gameOver) {
		playerIndicator->draw(sprites->at(GAME_SPRITE));
	}
}

void Connect::free() {
	if (board) {
		delete board;
	}
	if (sprites) {
		delete sprites;
	}
	if (countdown) {
		delete countdown;
	}
	if (playerIndicator) {
		delete playerIndicator;
	}
	if (players) {
		delete players;
	}
}

/*
Gets called by app state game play again
*/
void Connect::dropCheckers() {
	if (gameOver && board->lastCheckerFullyDropped()) {
		board->dropAllCheckers();
		reset = true;
	}
}

void Connect::resetGame() {
	if (!reset || !board->lastCheckerFullyDropped()) {
		return;
	}
	reset = false;
	gameOver = false;
	board->reset();
	countdown->reset(MOVE_TIME_LIMIT);
}

void Connect::updateTimer() {
	if (gameOver || !countdown->lessThanOneSecondBeforeTimesUp()) {
		return;
	}
	if (!canDropChecker) {
		canDropChecker = true;
		rotateTurns();
	} else {
		canDropChecker = false;
		countdown->reset(SWITCH_PLAYERS_TIME_LIMIT);
	}
}

/*
Gets called by app state game reset
*/
void Connect::startOver() {
	if (gameOver && board->lastCheckerFullyDropped()) {
		players->resetPlayerScoresAndWhosTurn();
		playerIndicator->setX(players->getCurrentPlayer()->getFontPosition().x - INDICATOR_X_OFFSET);
		dropCheckers();
	}
}

bool Connect::allPlayersLastCheckerInPlace() {
	return board->lastCheckerFullyDropped();
}

bool Connect::gameIsOver() const {
	return gameOver;
}

void Connect::rotateTurns() {
	players->rotateTurns();
	playerIndicator->setX(players->getCurrentPlayer()->getFontPosition().x - INDICATOR_X_OFFSET);
	countdown->reset(MOVE_TIME_LIMIT);
}