#include "GUIObjectManager.h"
#include "Selector.h"
#include "Button.h"
#include "Label.h"

GUIObjectManager::GUIObjectManager() : sprites(NULL) {

}

/* 
Loads all the GUI objects and GUI sprites from two different files
*/
bool GUIObjectManager::load(const char* filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Could not load: " << filename << "\n";
		return false;
	}
	int count = 0;
	file >> count;
	int type = 0;
	for (int i = 0; i < count; i++) {
		file >> type;
		switch ((OBJECT_TYPE)type) {
			case SELECTOR:
				GUIObjects.push_back(new Selector(file));
				break;
			case BUTTON:
				GUIObjects.push_back(new Button(file));
				break;
			case LABEL:
				GUIObjects.push_back(new Label(file));
				break;
			default:
				std::cout << "Error not a type: " << type << "\n";
				return false;
		};
	}
	file.close();
	sprites = new SpriteManager();
	if (!sprites->load(GUI_SPRITES_FILE)) {
		return false;
	}
	for (unsigned int i = 0; i < sprites->size(); i++) {
		if (i == GUIObject::NUMBERS || i == GUIObject::TEXT) {
			for (int j = 0; j < sprites->at(i)->getMaxColumns(); j++) {
				sprites->at(i)->changeTextureColorAt(j, Color(0, 0, 0));
			}
		}
	}
	return true;
}

/* 
Saves the GUI objects current numbers into a file
Gets called when you switch to game state
when game state gets called it opens the same file and reads them in
*/
void GUIObjectManager::save() {
	std::ofstream file(GAME_PARAMETERS);
	for (unsigned int i = 0; i < GUIObjects.size(); i++) {
		file << GUIObjects[i] << "\t";
	}
	file.close();
}

/* 
Whenever the mouse is clicked
Changes the value of whatever it is over
*/
int GUIObjectManager::onClick(int x, int y) {
	int changed = CHANGED_NOTHING;
	for (unsigned int i = 0; i < GUIObjects.size(); i++) {
		if (GUIObjects[i]->isOver(x, y)) {
			GUIObjects[i]->onClick(x, y);
			changed = i;
			break;
		}
	}
	//changes the rows and columns depending on the one that changes how many you need in a row
	changesTheMinimumAmountOfRowsAndColumns(changed);
	if (changed == TIME_LIMIT_BETWEEN_MOVES) {
		if (GUIObjects[changed]->modifies() == TIME_LIMIT_BETWEEN_MOVES) {
			if (((Selector*)GUIObjects[changed])->getCurrentNumber() == 1) {//makes it skip 1 second
				if (((Selector*)GUIObjects[changed])->clickedButton(((Selector*)GUIObjects[changed])->BUTTON_TOP, x, y)) {
					((Selector*)GUIObjects[changed])->setCurrentNumber(2);
				} else if (((Selector*)GUIObjects[changed])->clickedButton(((Selector*)GUIObjects[changed])->BUTTON_BOTTOM, x, y)) {
					((Selector*)GUIObjects[changed])->setCurrentNumber(0);
				}
			}
		}
	}
	//to be able to change to a different state
	if (changed > CHANGED_NOTHING) {
		return GUIObjects[changed]->modifies();
	} else {
		return 0;
	}
}

/* 
Whenever mouse wheel event is fired 
Changes the value of whatever it is over
*/
void GUIObjectManager::OnMouseWheel(bool Up, bool Down, int mX, int mY) {
	int changed = CHANGED_NOTHING;
	for (unsigned int i = 0; i < GUIObjects.size(); i++) {
		if (GUIObjects[i]->isOver(mX, mY)) {
			GUIObjects[i]->OnMouseWheel(Up, Down, mX, mY);
			changed = i;
		}
	}

	if (changed == TIME_LIMIT_BETWEEN_MOVES) {
		if (GUIObjects[changed]->modifies() == TIME_LIMIT_BETWEEN_MOVES) {//do not think I need this if
			if (((Selector*)GUIObjects[changed])->getCurrentNumber() == 1) {//makes it skip 1 second
				if (Up) {
					((Selector*)GUIObjects[changed])->setCurrentNumber(2);
				} else {
					((Selector*)GUIObjects[changed])->setCurrentNumber(0);
				}
			}
		}
	}
	changesTheMinimumAmountOfRowsAndColumns(changed);
}

/* 
Called whenever mouse wheel and clicked a button
Makes sure you have enough rows and columns to be able to win
*/
void GUIObjectManager::changesTheMinimumAmountOfRowsAndColumns(int changed) {
	if (changed == CHANGED_NOTHING) {
		return;
	}
	if (GUIObjects[changed]->modifies() == NUM_OF_CONNECTIONS_TO_WIN || GUIObjects[changed]->modifies() == NUM_OF_PLAYERS) {
		unsigned int i;
		for (i = 0; i < GUIObjects.size(); i++) {
			if (GUIObjects[i]->modifies() == NUM_OF_PLAYERS && GUIObjects[changed]->modifies() != NUM_OF_PLAYERS
				|| GUIObjects[i]->modifies() == NUM_OF_CONNECTIONS_TO_WIN && GUIObjects[changed]->modifies() != NUM_OF_CONNECTIONS_TO_WIN) {
				break;
			}
		}
		int biggestNumber = std::max(((Selector*)GUIObjects[changed])->getCurrentNumber(),
									 ((Selector*)GUIObjects[i])->getCurrentNumber());
		for (unsigned int j = 0; j < GUIObjects.size(); j++) {
			if (GUIObjects[j]->modifies() == NUM_OF_ROWS || GUIObjects[j]->modifies() == NUM_OF_COLUMNS) {
				((Selector*)GUIObjects[j])->setMinimumLimit(biggestNumber);
			}
		}
	}
}

/* 
Draws all GUI objects
*/
void GUIObjectManager::draw() {
	for (unsigned int i = 0; i < GUIObjects.size(); i++) {
		GUIObjects[i]->draw(sprites);
	}
}

/* 
Frees all GUI objects and all GUI sprites
*/
void GUIObjectManager::free() {
	for (unsigned int i = 0; i < GUIObjects.size(); i++) {
		delete GUIObjects[i];
	}
	GUIObjects.clear();
	if (sprites) {
		delete sprites;
	}
}