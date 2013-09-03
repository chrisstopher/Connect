#include "Button.h"

Button::Button(std::ifstream& file) : GUIObject(file) {
	file >> type;
	if (rect.x == CENTERED_X) {
		rect.x = (SCREEN_WIDTH - rect.w) / 2;
	}
	if (rect.y == CENTERED_Y) {
		rect.y = (SCREEN_HEIGHT - rect.h) / 2;
	}
}

Button::Button(Rect& newRect, int newChanges, int newType) : GUIObject(newRect, newChanges, newType) {
	rect.w = newRect.w;
	rect.h = newRect.h;
}

Button::~Button() {

}

void Button::draw(SpriteManager* sprites) {
	sprites->at(type)->start();
	sprites->at(type)->translateTo(rect.x, rect.y);
	sprites->at(type)->draw(0, 0, 0);
	sprites->at(type)->end();
}