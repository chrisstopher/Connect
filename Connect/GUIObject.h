#ifndef _GUIOBJECT_H_
#define _GUIOBJECT_H_

#include <fstream>
#include "Constants.h"
#include "SpriteManager.h"
#include "Rect.h"

class GUIObject {
public:
	GUIObject(std::ifstream& file);
	GUIObject(std::ifstream& file, int newType);
	GUIObject(std::ifstream& file, int newChange, int newType);
	GUIObject(Rect& newRect, int newChange, int newType);
	virtual void onClick(int x, int y);
	virtual void OnMouseWheel(bool Up, bool Down, int mX, int mY);
	bool isOver(int x, int y);
	virtual void draw(SpriteManager* sprites) = 0;
	int modifies() const;
	virtual void put(std::ostream& os);
	friend std::ostream& operator<<(std::ostream& os, GUIObject* obj);
	enum TYPE {//which sprite sheet to draw
		NOTHING = -1,
		NUMBERS,
		TEXT,
		BUTTON_ARROW_UP,
		BUTTON_ARROW_DOWN,
		BUTTON_START,
		BUTTON_BACK,
		BUTTON_RESET,
		BUTTON_PLAY_AGAIN
	};
protected:
	Rect rect;
	int changes;
	int type;
	enum ALIGNMENT {
		CENTERED_X = -1,
		CENTERED_Y = -1
	};
};


#endif
