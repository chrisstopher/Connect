#ifndef _LABEL_H_
#define _LABEL_H_

#include "GUIObject.h"
#include <string>

class Label : public GUIObject {
public:
	Label(std::ifstream& file);
	Label(Rect& rect, std::string& newText);
	virtual ~Label();
	void draw(SpriteManager* sprites);
	bool isAlphabet(char c);
	char convertToFrame(char c);
private:
	static const char FIRST_ALPHABET_CHAR = 'a', LAST_ALPHABET_CHAR = 'z';
	static const int TEXT_OFFSET = 20;
	std::string text;
};

#endif