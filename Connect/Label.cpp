#include "Label.h"

Label::Label(std::ifstream& file) : GUIObject(file, NOTHING, TEXT) {
	file >> text;
	rect.w = text.size() * TEXT_OFFSET;
	rect.h = TEXT_OFFSET;
	if (rect.x == CENTERED_X) {
		rect.x = (SCREEN_WIDTH - rect.w) / 2;
	}
	if (rect.y == CENTERED_Y) {
		rect.y = (SCREEN_HEIGHT - rect.h) / 2;
	}
}

Label::Label(Rect& rect, std::string& newText) : GUIObject(rect, NOTHING, TEXT), text(newText) {
	
}

Label::~Label() {
	
}

void Label::draw(SpriteManager* sprites) {
	sprites->at(type)->start();
	for (unsigned i = 0; i < text.size(); i++) {
		if (isAlphabet(text[i])) {//text[i] >= 'A' && text[i] <= 'Z') {
			sprites->at(type)->translateTo(rect.x + i * TEXT_OFFSET, rect.y);
			sprites->at(type)->draw(0, 0, convertToFrame(text[i]));
		}
	}
	sprites->at(type)->end();
}

bool Label::isAlphabet(char c) {
	return (c >= FIRST_ALPHABET_CHAR && c <= LAST_ALPHABET_CHAR);
}

char Label::convertToFrame(char c) {
	return c - FIRST_ALPHABET_CHAR;
}