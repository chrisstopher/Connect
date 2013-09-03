#include "PlayerManager.h"

PlayerManager::PlayerManager() : currentNode(NULL) {

}

/*
Deletes the allocated objects in the circular linked list and clears it
*/
PlayerManager::~PlayerManager() {
	Node<Player*>* n = playersCLinkedList.getHead();
	do {
		delete n->getObject();
		n = n->getNext();
	} while (n != playersCLinkedList.getHead());

	playersCLinkedList.clear();
}

/*
Makes sure the playerCount is atleast MIN_PLAYER_LIMIT and at most MAX_PLAYER_LIMIT
Creates the colors and creates the players
Assigns the colors to the players
Sets the currentNode to the head of the players 
*/
bool PlayerManager::load(unsigned playerCount) {
	if (playerCount < MIN_PLAYER_LIMIT || playerCount > MAX_PLAYER_LIMIT) {
		std::cout << "There can only be " << MIN_PLAYER_LIMIT << " to " << MAX_PLAYER_LIMIT << " players.\n";
		return false;
	}
	Color* playerColors = new Color[playerCount];
	playerColors[0] = Color(193, 27, 23);//red
	playerColors[1] = Color(23, 65, 163);//blue
	if (playerCount >= 3) {
		playerColors[2] = Color(65, 163, 23);//green
	}
	if (playerCount == 4) {
		playerColors[3] = Color(128, 0, 128, 255);//purple
	}
	const int SPACING_BETWEEN_PLAYERS = SCREEN_WIDTH / 4;
	for (unsigned i = 0; i < playerCount; i++) {
		playersCLinkedList.push_back(new Player(i + 1, 
									 playerColors[i],
									 Position(SCREEN_WIDTH / 2 + SPACING_BETWEEN_PLAYERS / 2 * ((i - (playerCount - 1) + i % playerCount)),
											  SCREEN_HEIGHT / 32)));
	}
	currentNode = playersCLinkedList.getHead();
	delete [] playerColors;
	return true;
}

/*
Draws each player in the circular link list
*/
void PlayerManager::draw(Sprite* font) {
	Node<Player*>* n = playersCLinkedList.getHead();
	do {
		n->getObject()->draw(font);
		n = n->getNext();
	} while (n != playersCLinkedList.getHead());
}

void PlayerManager::rotateTurns() {
	currentNode = currentNode->getNext();
}

Player* PlayerManager::getCurrentPlayer() {
	return currentNode->getObject();
}

/*
Resets each player in the circular link list
Sets the current node to the head
*/
void PlayerManager::resetPlayerScoresAndWhosTurn() {
	Node<Player*>* n = playersCLinkedList.getHead();
	do {
		n->getObject()->setScoreToZero();
		n = n->getNext();
	} while (n != playersCLinkedList.getHead());
	currentNode = playersCLinkedList.getHead();
}