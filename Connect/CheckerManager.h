#ifndef _CHECKERMANAGER_H_
#define _CHECKERMANAGER_H_

#include <vector>
#include "Checker.h"
#include "Sprite.h"
#include "Oscillator.h"
#include "Globals.h"
#include "Constants.h"

class CheckerManager {
public:
	CheckerManager();
	~CheckerManager();
	void add(Checker* checker);
	void update();
	void draw(Sprite* sprite);
	void clear();
	bool lastCheckerDropInPlace();
	void dropAllCheckers();
	bool fading();
	void fadeTheCheckersAt(std::vector<Position>& positions);
	Position& getLastCheckerDroppedPosition();
	unsigned int size() const;
private:
	std::vector<Checker*> checkers;
	static const int ALPHA_DEFAULT = 255;
	Oscillator fader;
	std::vector<int> winningCheckersIndexes;
	static const int CHECKER_FRAME = 1;
};

#endif