#include "Connect.h"

Connect::Connect(int players, Timer* timer, int connectAmount, int rows, int columns)
	: PLAYER_COUNT(players),
	  CONNECT_AMOUNT(connectAmount),
	  ROWS(rows), COLUMNS(columns),
	  MIN_ROWS(connectAmount), MIN_COLUMNS(connectAmount),
	  MOVE_TIME_LIMIT(timer->getDelayInSeconds() > 0 ? timer->getDelayInSeconds() + 1 : 0),
      connectStateManager(new ConnectStateManager(this)),
	  sprites(NULL),
	  board(NULL),
	  players(NULL),
	  boardColor(0, 0, 0),
	  countdown(timer),
	  COUNTDOWN_POSITION(SCREEN_WIDTH / 2 - FONT_WIDTH / 2, 64),
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

void Connect::onClick(int mX, int mY) {
    connectStateManager->onClick(mX, mY, players, board);
}

void Connect::onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
    connectStateManager->onMouseMove(mX, mY, board, players->getCurrentPlayer()->getColor());
}

void Connect::logic() {
	playerIndicator->update();
	board->update();
    connectStateManager->update(countdown, MOVE_TIME_LIMIT, SWITCH_PLAYERS_TIME_LIMIT, board);
}

/*
Draws different things depending on the state
Draws the board
Draws the player indicator
*/
void Connect::draw() {
    connectStateManager->draw(sprites, players->getCurrentPlayer(), playerIndicator, countdown, COUNTDOWN_POSITION);
    players->draw(sprites->at(SpriteManager::FONT_SPRITE));
	board->draw(sprites->at(SpriteManager::GAME_SPRITE));
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
    if (connectStateManager) {
        delete connectStateManager;
    }
}

/*
Gets called by app state game play again
*/
void Connect::dropCheckers() {
    board->dropAllCheckers();
    connectStateManager->setState(connectStateManager->getResettingState());
}

/*
Gets called by app state game reset
*/
void Connect::startOver() {
    players->resetPlayerScoresAndWhosTurn();
	playerIndicator->setX(players->getCurrentPlayer()->getFontPosition().x - INDICATOR_X_OFFSET);
	dropCheckers();
}

bool Connect::allPlayersLastCheckerInPlace() {
	return board->lastCheckerFullyDropped();
}

bool Connect::gameIsOver() const {
	return connectStateManager->gameOver();
}

void Connect::rotateTurns() {
	players->rotateTurns();
	playerIndicator->setX(players->getCurrentPlayer()->getFontPosition().x - INDICATOR_X_OFFSET);
	countdown->reset(MOVE_TIME_LIMIT);
}