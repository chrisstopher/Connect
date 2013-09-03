#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "GUIObject.h"
#include "SpriteManager.h"
#include <fstream>

class Button : public GUIObject {
public:
	Button(std::ifstream& file);
	Button(Rect& newRect, int newChanges, int newType);
	virtual ~Button();
	void draw(SpriteManager* sprites);
private:
};

#endif
