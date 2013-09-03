#ifndef _SELECTOR_H_
#define _SELECTOR_H_

#include "GUIObject.h"
#include "Button.h"
#include "Label.h"
#include "Sprite.h"
#include "Counter.h"
#include <vector>
#include <string>

class Selector : public GUIObject {
public:
	Selector(std::ifstream& file);
	virtual ~Selector();
	void onClick(int x, int y);
	void OnMouseWheel(bool Up, bool Down, int mX, int mY);
	void draw(SpriteManager* sprites);
	void setCurrentNumber(int i);
	int getCurrentNumber() const;
	void setMinimumLimit(int i);
	int getCurrentMinimum() const;
	void put(std::ostream& os);
	enum BUTTONS { BUTTON_TOP = 0, BUTTON_BOTTOM };
	bool clickedButton(BUTTONS i, int x, int y);
private:
	Counter currentNumber;
	int minimumLimit, maximumLimit;
	static const int BUTTON_COUNT = 2;
	std::string modifies;
	std::vector<Button*> Buttons;
	int buttonPosition;
	Label* label;
	enum BUTTON_POSITIONS {
		LEFT = 0,
		RIGHT
	};
};

#endif
