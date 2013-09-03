#include "Selector.h"

Selector::Selector(std::ifstream& file)
		: GUIObject(file, NUMBERS), currentNumber(0, Position(rect.x + 24, rect.y)) {
	int curNum = 0;
	file >>  buttonPosition >> minimumLimit >> curNum >> maximumLimit >> modifies;
	currentNumber.set(curNum);

	if (currentNumber.getCount() < minimumLimit) {
		currentNumber = minimumLimit;
	}
	std::string text;
	getline(file, text);
	
	text.erase(text.find_first_of('\t'), 1);
	const int TEXT_OFFSET = 300;
	label = new Label(Rect(rect.x - TEXT_OFFSET, rect.y, 0, 0), text);
	Buttons.reserve(BUTTON_COUNT);
	int buttonPositionX = rect.x;
	if ((BUTTON_POSITIONS)buttonPosition == RIGHT) {
		buttonPositionX = (rect.x + rect.w) - 16;
		currentNumber.setX(rect.x + 8);
	}
	for (int i = 0; i < BUTTON_COUNT; i++) {
		Buttons.push_back(new Button(Rect(buttonPositionX, rect.y + i * 8, 16, 8), i,
									 BUTTON_ARROW_UP + i));
	}
}

Selector::~Selector() {
	if (label) {
		delete label;
	}
	for (unsigned int i = 0; i < Buttons.size(); i++) {
		delete Buttons[i];
	}
	Buttons.clear();
}

void Selector::onClick(int x, int y) {
	for (int i = 0; i < 2; i++) {
		if (Buttons[i]->isOver(x, y)) {
			if (i == 0) {
				if (currentNumber.getCount() < maximumLimit) {
					currentNumber.incre();
				}
			} else {
				if (currentNumber.getCount() > minimumLimit) {
					currentNumber.incre(-1);
				}
			}
		}
	}
}

void Selector::OnMouseWheel(bool Up, bool Down, int mX, int mY) {
	if (Up) {
		if (currentNumber.getCount() < maximumLimit) {
			currentNumber.incre();
		}
	} else {
		if (currentNumber.getCount() > minimumLimit) {
			currentNumber.incre(-1);
		}
	}
}

void Selector::draw(SpriteManager* sprites) {
	for (int i = 0; i < BUTTON_COUNT; i++) {
		Buttons[i]->draw(sprites);
	}
	label->draw(sprites);
	sprites->at(type)->start();
	currentNumber.draw(sprites->at(type), Color());
	sprites->at(type)->end();
}

void Selector::setCurrentNumber(int i) {
	currentNumber.set(i);
}

int Selector::getCurrentNumber() const {
	return currentNumber.getCount();
}

void Selector::setMinimumLimit(int i) {
	if (currentNumber.getCount() < i) {
		currentNumber.set(i);
	}
	minimumLimit = i;
}

int Selector::getCurrentMinimum() const {
	return minimumLimit;
}

void Selector::put(std::ostream& os) {
	os << getCurrentNumber();
}

bool Selector::clickedButton(BUTTONS i, int x, int y) {
	return Buttons[i]->isOver(x, y);
}