//Code from http://www.sdltutorials.com/sdl-app-states
//Modified to what I needed on my menu
//=============================================================================
#include "AppStateMenu.h"

#include "AppStateManager.h"

//=============================================================================
AppStateMenu AppStateMenu::Instance;

//=============================================================================
AppStateMenu::AppStateMenu() : gui(NULL) {
	
}

//=============================================================================
void AppStateMenu::OnActivate() {
	gui = new GUIObjectManager();
	if (!gui->load(GUI_MENU)) {//could have a bool loaded and whatnot
		std::cout << "Could not load: " << GUI_MENU << ".\n";
		AppStateManager::SetActiveAppState(APPSTATE_NONE);
		return;
	}
}

void AppStateMenu::OnLButtonUp(int mX, int mY) {
	int changed = gui->onClick(mX, mY/*, changeToGame*/);
	switch ((GUIObjectManager::OBJECT_CHANGES)changed) {
		case GUIObjectManager::STATE:
			AppStateManager::SetActiveAppState(APPSTATE_GAME);
		break;
		default:
		break;
	}
}

void AppStateMenu::OnMouseWheel(bool Up, bool Down, int mX, int mY) {
	gui->OnMouseWheel(Up, Down, mX, mY);
}

void AppStateMenu::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym) {
		case SDLK_s:
		case SDLK_SPACE:
		case SDLK_RETURN:
			AppStateManager::SetActiveAppState(APPSTATE_GAME);
			break;
		case SDLK_ESCAPE:
			AppStateManager::SetActiveAppState(APPSTATE_NONE);
			break;
		default:
			break;
	}
}

//-----------------------------------------------------------------------------
void AppStateMenu::OnLoop() {
	
}

//-----------------------------------------------------------------------------
void AppStateMenu::OnRender() {
	gui->draw();
}

//-----------------------------------------------------------------------------
void AppStateMenu::OnDeactivate() {
	gui->save();
	gui->free();
	if (gui) {
		delete gui;
	}
}

//=============================================================================
AppStateMenu* AppStateMenu::GetInstance() {
	return &Instance;
}

//=============================================================================
