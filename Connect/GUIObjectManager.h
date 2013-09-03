#ifndef _GUIOBJECTMANAGER_H_
#define _GUIOBJECTMANAGER_H_

#include <vector>
#include <fstream>
#include "GUIObject.h"
#include "SpriteManager.h"
#include "FileNames.h"

class GUIObjectManager {
public:
	GUIObjectManager();
	bool load(const char* filename);
	void save();
	int onClick(int x, int y);
	void OnMouseWheel(bool Up, bool Down, int mX, int mY);
	void draw();
	void free();

	enum OBJECT_CHANGES {
		NOTHING = -1,
		NUM_OF_PLAYERS,
		TIME_LIMIT_BETWEEN_MOVES,
		NUM_OF_CONNECTIONS_TO_WIN,
		NUM_OF_ROWS,
		NUM_OF_COLUMNS,
		STATE,
		RESET,
		PLAY_AGAIN
	};
private:
	std::vector<GUIObject*> GUIObjects;
	SpriteManager* sprites;
	enum OBJECT_TYPE {
		BUTTON = 0,
		SELECTOR,
		LABEL
	};
	static const int CHANGED_NOTHING = -1;
	void changesTheMinimumAmountOfRowsAndColumns(int changed);
};

#endif
