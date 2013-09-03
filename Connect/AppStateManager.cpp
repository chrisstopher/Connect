//Code from http://www.sdltutorials.com/sdl-app-states

//=============================================================================
#include "AppStateManager.h"
#include "AppStateMenu.h"
#include "AppStateGame.h"

//=============================================================================
AppState* AppStateManager::ActiveAppState = 0;

//=============================================================================
void AppStateManager::OnEvent(SDL_Event* EventHolder) {
	if(ActiveAppState) ActiveAppState->OnEvent(EventHolder);
}

//-----------------------------------------------------------------------------
void AppStateManager::OnLoop() {
	if(ActiveAppState) ActiveAppState->OnLoop();
}

//-----------------------------------------------------------------------------
void AppStateManager::OnRender() {
	if(ActiveAppState) ActiveAppState->OnRender();
}

//=============================================================================
void AppStateManager::SetActiveAppState(APPSTATE AppStateID) {
	if (ActiveAppState) {
		ActiveAppState->OnDeactivate();
	}

	switch (AppStateID) {
		case APPSTATE_NONE:
			ActiveAppState = 0;
			break;
		case APPSTATE_MENU:
			ActiveAppState = AppStateMenu::GetInstance();
			break;
		case APPSTATE_GAME:
			ActiveAppState = AppStateGame::GetInstance();
			break;
		default:
			ActiveAppState = 0;
			break;
	}

	if (ActiveAppState) {
		ActiveAppState->OnActivate();
	}
}

//-----------------------------------------------------------------------------
AppState* AppStateManager::GetActiveAppState() {
	return ActiveAppState;
}

//=============================================================================
