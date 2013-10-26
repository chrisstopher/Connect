#ifndef _SPRITEMANAGER_H_
#define _SPRITEMANAGER_H_

#include <fstream>
#include <vector>
#include "Sprite.h"
#include <string>

#include "FileNames.h"

class SpriteManager {
public:
	SpriteManager();
	~SpriteManager();
	bool load(const char* filename);
	unsigned size();
	Sprite* at(unsigned i);
    enum SPRITE_INDEXES {
		GAME_SPRITE = 0,
		FONT_SPRITE = 1,
	};
private:
	std::vector<Sprite*> Sprites;
};

#endif