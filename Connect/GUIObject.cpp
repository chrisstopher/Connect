#include "GUIObject.h"

GUIObject::GUIObject(std::ifstream& file) {
	file >> rect.x >> rect.y >> rect.w >> rect.h >> changes;
}

GUIObject::GUIObject(std::ifstream& file, int newType) : type(newType) {
	file >> rect.x >> rect.y >> rect.w >> rect.h >> changes;
}

GUIObject::GUIObject(std::ifstream& file, int newChange, int newType) : changes(newChange), type(newType) {
	file >> rect.x >> rect.y;
}

GUIObject::GUIObject(Rect& newRect, int newChange, int newType) : rect(newRect), changes(newChange), type(newType) {
	
}

void GUIObject::onClick(int x, int y) {

}

void GUIObject::OnMouseWheel(bool Up, bool Down, int mX, int mY) {
	
}

bool GUIObject::isOver(int x, int y) {
	return (x <= rect.x + rect.w && x >= rect.x && y <= rect.y + rect.h && y >= rect.y);
}

int GUIObject::modifies() const {
	return changes;
}

void GUIObject::put(std::ostream& os) {
	
}

std::ostream& operator<<(std::ostream& os, GUIObject* obj) {
	obj->put(os);
	return os;
}