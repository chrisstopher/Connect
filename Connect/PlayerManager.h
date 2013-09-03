#ifndef _PLAYERMANAGER_H_
#define _PLAYERMANAGER_H_

#include "CLinkedList.h"
#include "Player.h"
#include "Constants.h"

class PlayerManager {
public:
	PlayerManager();
	~PlayerManager();
	bool load(unsigned playerCount);
	void update();
	void draw(Sprite* font);
	void rotateTurns();
	Player* getCurrentPlayer();
	void resetPlayerScoresAndWhosTurn();
private:
	CLinkedList<Player*> playersCLinkedList;
	Node<Player*>* currentNode;
	static const int MIN_PLAYER_LIMIT = 2, MAX_PLAYER_LIMIT = 4;
};

#endif