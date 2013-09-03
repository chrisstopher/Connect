#include "Board.h"
#include "Player.h"

/*
Return true if the x value of position 1 is less than the x value of position 2
*/
struct {
	bool operator() (Position& p1, Position& p2) {
		return p1.x < p2.x;
	}
} byX;

/*
Return true if the y value of position 1 is less than the y value of position 2
*/
struct {
	bool operator() (Position& p1, Position& p2) {
		return p1.y < p2.y;
	}
} byY;

/*
Creates the grid and position 2d arrays
Sets each value in the grid to NO_CHECKER
Sets each position in the position array to the appropriate position
*/
Board::Board(int connect, int rows, int columns, int id, Color& newColor, Position& startingPosition) : connectCount(connect), frame(id), color(newColor) {
	grid.create(columns, rows);
	position.create(columns, rows);
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < columns; x++) {
			grid(x, y) = NO_CHECKER;
			position(x, y).x = x * SPRITE_WIDTH + startingPosition.x;
			position(x, y).y = y * SPRITE_HEIGHT + startingPosition.y;
		}
	}
}

Board::~Board() {
	grid.clear();
	position.clear();
}

/*
Rect collision on a position
*/
bool Board::isOver(int x, int y) {
	return (x >= position(0, 0).x && x <= position(position.maxColumns()-1, position.maxRows()-1).x
				+ (position(1, 0).x - position(0, 0).x) &&
			y >= position(0, 0).y && y <= position(position.maxColumns()-1, position.maxRows()-1).y
				+ (position(0, 1).y - position(0, 0).y));
}

/*
returns the index for the 2d array for the column
*/
int Board::convertToColumnIndex(int i) {
	return (i - position(0, 0).x) / SPRITE_WIDTH;
}

/*
returns the index for the 2d array for the row
*/
int Board::convertToRowIndex(int i) {
	return (i - position(0, 0).y) / SPRITE_HEIGHT;
}

/*
Checks the first row in the column for no checker
If there is a checker then it returns false
*/
bool Board::columnIsNotFull(int x) {
	return (grid(convertToColumnIndex(x), 0) == NO_CHECKER);
}

/*
columnIsNotFull and isOver has to be called before this gets called that is what makes the last return not get reached
Traverses a column to find the position in the column that has a checker below it
or if there is no checker in the column and puts it there
*/
Position& Board::setEndingPosition(int x, int type) {
	x = convertToColumnIndex(x);
	for (int y = 0; y < grid.maxRows(); y++) {
		if (y + 1 > grid.maxRows()-1 || grid(x, y + 1) != NO_CHECKER) {
			grid(x, y) = type;
			return position(x, y);
		}
	}
	return position(0, 0);//should never get reached
}

/*
Checks if the column * rows is the number of checkers on the board
*/
bool Board::full() {
	return grid.maxColumns() * grid.maxRows() == checkers.size();
}

void Board::add(Checker* checker) {
	checkers.add(checker);
}
/*
Updates the checkers positions
If you have checkers winning positions they get sorted by there x and then there y then call unique to make sure there is no duplicates
Sorts the winning checker position by there x value and then there y value
Then pulls out the uniques if any
Then alerts the checker list which ones to fade
*/
void Board::update() {
	checkers.update();
	if (!winningCheckersPositions.empty() && checkers.lastCheckerDropInPlace() && !checkers.fading()) {
		std::sort(winningCheckersPositions.begin(), winningCheckersPositions.end(), byX);
		std::sort(winningCheckersPositions.begin(), winningCheckersPositions.end(), byY);
		std::vector<Position>::iterator it = std::unique(winningCheckersPositions.begin(), winningCheckersPositions.end());
		winningCheckersPositions.resize(std::distance(winningCheckersPositions.begin(), it));
		checkers.fadeTheCheckersAt(winningCheckersPositions);
	}
}

/*
Makes sure there is atleast enough checkers on the board to even check for a win
Checks the column, row, and diagnols depending on which one the user dropped in...
*/
bool Board::hasBeenWonBy(Player* player) {
	if (checkers.size() < connectCount) {
		return false;
	}
	int columnOfLastCheckerDropped = convertToColumnIndex(checkers.getLastCheckerDroppedPosition().x),
		rowOfLastCheckerDropped = convertToRowIndex(checkers.getLastCheckerDroppedPosition().y);
	bool won = false;
	if (testsTheColumn(columnOfLastCheckerDropped, rowOfLastCheckerDropped, player->getID())) {
		won = true;
	}
	if (testsTheRow(columnOfLastCheckerDropped, rowOfLastCheckerDropped, player->getID())) {
		won = true;
	}
	if (testsNorthWestToSouthEastLeftSide(columnOfLastCheckerDropped, rowOfLastCheckerDropped, player->getID())) {
		won = true;
	}
	if (testsNorthWestToSouthEastTopSide(columnOfLastCheckerDropped, rowOfLastCheckerDropped, player->getID())) {
		won = true;
	}
	if (testsNorthEastToSouthWestTopSide(columnOfLastCheckerDropped, rowOfLastCheckerDropped, player->getID())) {
		won = true;
	}
	if (testsNorthEastToSouthWestRightSide(columnOfLastCheckerDropped, rowOfLastCheckerDropped, player->getID())) {
		won = true;
	}
	return won;
}

bool Board::testsTheColumn(int column, int row, int playerId) {
	int whichRowToStartChecking = row - (connectCount - 1);
	if (whichRowToStartChecking < 0) {
		whichRowToStartChecking = 0;
	}
	row++;
	int howManyLoopsPerColumn = std::min(row, (grid.maxRows() - (connectCount - 1)));
	for (int y = whichRowToStartChecking; y < howManyLoopsPerColumn; y++) {
		if (testsTheColumnForConnectCount(y, column, playerId)) {
			for (int i = y; i < y + connectCount; i++) {
				winningCheckersPositions.push_back(position(column, i));
				
			}
			return true;
		}
	}
	return false;
}

//Checks for how many you want to check for at the starting position 
bool Board::testsTheColumnForConnectCount(int startAt, int whichColumn, int playerId) {
	for (int i = startAt; i < startAt + connectCount; i++) {
		if (grid(whichColumn, i) != playerId) {
			return false;
		}
	}
	return true;
}

bool Board::testsTheRow(int column, int row, int playerId) {
	for (int i = grid.maxColumns(); i > connectCount-1; i--) {
		int whichColumnToStartChecking = column - (i - 1);
		if (whichColumnToStartChecking < 0) {
			whichColumnToStartChecking = 0;
		}
		int newColumn = column + 1;
		int howManyLoopsPerRow = std::min(newColumn, (grid.maxColumns() - (i - 1)));
		if (testsTheRowAt(whichColumnToStartChecking, row, howManyLoopsPerRow, i, playerId)) {
			return true;
		}
	}
	return false;
}

bool Board::testsTheRowAt(int columnToStartAt, int row, int howManyLoops, int count, int playerId) {
	for (int x = columnToStartAt; x < howManyLoops; x++) {
		if (testsForAnAmountInRow(count, x, row, playerId)) {
			for (int i = x; i < x + count; i++) {
				winningCheckersPositions.push_back(position(i, row));
			}
			return true;
		}
	}
	return false;
}

bool Board::testsForAnAmountInRow(int count, int startAt, int whichRow, int playerId) {
	for (int i = startAt; i < startAt + count; i++) {
		if (grid(i, whichRow) != playerId) {
			return false;
		}
	}
	return true;
}

/*
Assuming the connectCount is 4 then...
Blanks and - not checked either
Checks these * spots and checks and starts at S depending on which column you drop in
  0 1 2 3 4 5 6
0 S
1 S *
2 S * *
3 - * * *
4 - - * * *
5 - - - * * *
*/
bool Board::testsNorthWestToSouthEastLeftSide(int column, int row, int playerId) {
	int diagnolStartsAt = row - column;
	int canOnlyStartAt = std::min(diagnolStartsAt, grid.maxRows() - connectCount);
	if (canOnlyStartAt < 0 || diagnolStartsAt < 0) {//not on my side
		return false;
	}
	for (int i = canOnlyStartAt; i >= diagnolStartsAt; i--) {
		int howManyToConnect = grid.maxRows() - i;
		if (howManyToConnect > grid.maxColumns()) {
			howManyToConnect = grid.maxColumns();
		}
		for (int j = howManyToConnect; j >= connectCount; j--) {
			if (testsNorthWestToSouthEastLeftSideStartingAt(i, column, j, playerId)) {
				return true;
			}
		}
	}
	return false;
}

bool Board::testsNorthWestToSouthEastLeftSideStartingAt(int startAt, int column, int howManyToConnect, int playerId) {
	int loopCount = ((grid.maxRows() - howManyToConnect) + 1) - startAt;
	if (loopCount + howManyToConnect-1 > grid.maxColumns()) {
		loopCount = grid.maxColumns() - (howManyToConnect-1);
	}
	int newColumn = column + 1;
	loopCount = std::min(newColumn, loopCount);
	int startHere = column - (howManyToConnect - 1);
	if (startHere < 0) {
		startHere = 0;
	}
	Position startingHere;
	for (int i = startHere; i < loopCount; i++) {
		startingHere.x = i;
		startingHere.y = startAt + i;
		if (testsNorthWestToSouthEast(howManyToConnect, startingHere, playerId)) {
			for (int j = 0; j < howManyToConnect; j++) {
				winningCheckersPositions.push_back(position(startingHere.x + j, startingHere.y + j));
			}
			return true;
		}
	}
	return false;
}

/*
Assuming the connectCount is 4 then...
Blanks and - not checked either
Checks these * spots and checks and starts at S depending on which column you drop in
  0 1 2 3 4 5 6
0   S S S - - -
1     * * * - -
2       * * * - 
3         * * *
4           * *
5             *
*/
bool Board::testsNorthWestToSouthEastTopSide(int column, int row, int playerId) {
	int diagnolStartsAt = column - row;
	int canOnlyStartAt = std::min(diagnolStartsAt, grid.maxColumns() - connectCount);
	if (canOnlyStartAt < 1 || diagnolStartsAt < 1) {//not on my side
		return false;
	}
	if (diagnolStartsAt > canOnlyStartAt) {
		return false;
	}
	for (int i = canOnlyStartAt; i <= diagnolStartsAt; i++) {
		int howManyToConnect = grid.maxColumns() - i;
		if (howManyToConnect > grid.maxRows()) {
			howManyToConnect = grid.maxRows();
		}
		for (int j = howManyToConnect; j >= connectCount; j--) {
			if (testsNorthWestToSouthEastTopSideStartingAt(i, row, j, playerId)) {
				return true;
			}
		}
	}
	return false;
}

bool Board::testsNorthWestToSouthEastTopSideStartingAt(int startAt, int row, int howManyToConnect, int playerId) {
	int loopCount = ((grid.maxColumns() - howManyToConnect) + 1) - startAt;
	if (loopCount + howManyToConnect-1 > grid.maxRows()) {
		loopCount = grid.maxRows() - (howManyToConnect-1);
	}
	int newRow = row + 1;
	loopCount = std::min(newRow, loopCount);
	int startHere = row - (howManyToConnect - 1);
	if (startHere < 0) {
		startHere = 0;
	}
	Position startingHere;
	for (int i = startHere; i < loopCount; i++) {
		startingHere.x = startAt + i;
		startingHere.y = i;
		if (testsNorthWestToSouthEast(howManyToConnect, startingHere, playerId)) {
			for (int j = 0; j < howManyToConnect; j++) {
				winningCheckersPositions.push_back(position(startingHere.x + j, startingHere.y + j));
			}
			return true;
		}
	}
	return false;
}

bool Board::testsNorthWestToSouthEast(int count, Position& startAt, int playerId) {
	for (int i = 0; i < count; i++) {
		if (grid(startAt.x + i, startAt.y + i) != playerId) {
			return false;
		}
	}
	return true;
}

/*
Assuming the connectCount is 4 then...
Blanks and - not checked either
Blanks will result in negative indexes and breaks out early
Checks these * spots and checks and starts at S depending on which column you drop in
  0 1 2 3 4 5 6
0 - - - S S S
1 - - * * *
2 - * * *
3 * * *
4 * *
5 *
*/
bool Board::testsNorthEastToSouthWestTopSide(int column, int row, int playerId) {
	int diagnolStartsAt = ((grid.maxColumns()-1) - column - row);
	int canOnlyStartAt = std::min(diagnolStartsAt, grid.maxColumns() - connectCount);
	if (canOnlyStartAt < 1 || diagnolStartsAt < 1) {//not on my side
		return false;
	}
	if (diagnolStartsAt > canOnlyStartAt) {
		return false;
	}
	for (int i = canOnlyStartAt; i >= diagnolStartsAt; i--) {
		int howManyToConnect = grid.maxColumns() - i;
		if (howManyToConnect > grid.maxRows()) {
			howManyToConnect = grid.maxRows();
		}
		for (int j = howManyToConnect; j >= connectCount; j--) {
			if (testsNorthEastToSouthWestTopSideStartingAt(i, row, j, playerId)) {
				return true;
			}
		}
	}
	return false;
}

bool Board::testsNorthEastToSouthWestTopSideStartingAt(int startAt, int row, int howManyToConnect, int playerId) {
	int loopCount = ((grid.maxColumns() - howManyToConnect) + 1) - startAt;
	if (loopCount + howManyToConnect-1 > grid.maxRows()) {
		loopCount = grid.maxRows() - (howManyToConnect-1);
	}
	int newRow = row + 1;
	loopCount = std::min(newRow, loopCount);
	int startHere = row - (howManyToConnect - 1);
	if (startHere < 0) {
		startHere = 0;
	}
	Position startingHere;
	for (int i = startHere; i < loopCount; i++) {
		startingHere.x = (grid.maxColumns() - 1) - startAt - i;
		startingHere.y = i;
		if (testsNorthEastToSouthWest(howManyToConnect, startingHere, playerId)) {
			for (int j = 0; j < howManyToConnect; j++) {
				winningCheckersPositions.push_back(position(startingHere.x - j, startingHere.y + j));
			}
			return true;
		}
	}
	return false;
}

/*
Assuming the connectCount is 4 then...
Blanks and - not checked either
Blanks will result in negative indexes and breaks out early
Checks these * spots and checks and starts at S depending on which column you drop in
  0 1 2 3 4 5 6
0             S
1           * S
2         * * S
3       * * * -
4     * * * - -
5   * * * - - -
*/
bool Board::testsNorthEastToSouthWestRightSide(int column, int row, int playerId) {
	int diagnolStartsAt = row - ((grid.maxColumns()-1) - column);
	int canOnlyStartAt = std::min(diagnolStartsAt, grid.maxRows() - connectCount);
	if (diagnolStartsAt < 0 || canOnlyStartAt < 0) {
		return false;
	}
	for (int i = canOnlyStartAt; i >= diagnolStartsAt; i--) {
		int howManyToConnect = grid.maxRows() - i;
		if (howManyToConnect > grid.maxColumns()) {
			howManyToConnect = grid.maxColumns();
		}
		for (int j = howManyToConnect; j >= connectCount; j--) {
			if (testsNorthEastToSouthWestRightSideStartingAt(i, column, j, playerId)) {
				return true;
			}
		}
	}
	return false;
}

bool Board::testsNorthEastToSouthWestRightSideStartingAt(int startAt, int column, int howManyToConnect, int playerId) {
	int loopCount = ((grid.maxRows() - howManyToConnect) + 1) - startAt;
	if (loopCount + howManyToConnect-1 > grid.maxColumns()) {
		loopCount = grid.maxColumns() - (howManyToConnect-1);
	}
	int newColumn = ((grid.maxColumns()-1) - column) + 1;
	loopCount = std::min(newColumn, loopCount);
	int startHere = ((grid.maxColumns()-1) - column) - (howManyToConnect - 1);
	if (startHere < 0) {
		startHere = 0;
	}
	Position startingHere;
	for (int i = startHere; i < loopCount; i++) {
		startingHere.x = (grid.maxColumns() - 1) - i;
		startingHere.y = startAt + i;
		if (testsNorthEastToSouthWest(howManyToConnect, startingHere, playerId)) {
			for (int j = 0; j < howManyToConnect; j++) {
				winningCheckersPositions.push_back(position(startingHere.x - j, startingHere.y + j));
			}
			return true;
		}
	}
	return false;
}

bool Board::testsNorthEastToSouthWest(int count, Position& startAt, int playerId) {
	for (int i = 0; i < count; i++) {
		if (grid(startAt.x - i, startAt.y + i) != playerId) {
			return false;
		}
	}
	return true;
}

/*
Draws all checkers and the board
*/
void Board::draw(Sprite* sprite) {
	sprite->start();
	checkers.draw(sprite);
	sprite->changeTextureColorAt(frame, color);
	for (int y = 0; y < position.maxRows(); y++) {
		for (int x = 0; x < position.maxColumns(); x++) {
			sprite->translateTo(position(x, y).x, position(x, y).y);
			sprite->draw(0, 0, frame);
		}
	}
	sprite->end();
}

/*
clears out the winning checker positions, all the checkers, and resets the whole grid to have no checkers
*/
void Board::reset() {
	winningCheckersPositions.clear();
	checkers.clear();
	for (int y = 0; y < grid.maxRows(); y++) {
		for (int x = 0; x < grid.maxColumns(); x++) {
			grid(x, y) = NO_CHECKER;
		}
	}
}

Position& Board::startingPosition() {
	return position(0, 0);
}

void Board::dropAllCheckers() {
	checkers.dropAllCheckers();
}

bool Board::lastCheckerFullyDropped() {
	return checkers.lastCheckerDropInPlace();
}