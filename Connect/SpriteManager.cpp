#include "SpriteManager.h"

SpriteManager::SpriteManager() {

}

SpriteManager::~SpriteManager() {
	for (unsigned i = 0; i < Sprites.size(); i++) {
		delete Sprites[i];
	}
	Sprites.clear();
}

bool SpriteManager::load(const char* filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Could not open: " << filename << "\n";
		return false;
	}
	std::string spriteName;
	int spriteWidth, spriteHeight;
	while (file >> spriteName >> spriteWidth >> spriteHeight) {
		Sprites.push_back(new Sprite(std::string(IMAGE_DIR) + spriteName, spriteWidth, spriteHeight));
		if (!Sprites[Sprites.size()-1]->load()) {
			return false;
		}
	}
	file.close();
	return true;
}

unsigned SpriteManager::size() {
	return Sprites.size();
}

Sprite* SpriteManager::at(unsigned i) {
	return Sprites[i];
}