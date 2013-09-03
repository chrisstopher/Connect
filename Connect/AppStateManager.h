//=============================================================================
#ifndef __APPSTATEMANAGER_H__
	#define __APPSTATEMANAGER_H__

//Code from http://www.sdltutorials.com/sdl-app-states

#include "AppState.h"

//=============================================================================
enum APPSTATE {
	APPSTATE_NONE = 0,
	APPSTATE_INTRO,
	APPSTATE_MENU,
	APPSTATE_GAME,
	APPSTATE_CREDITS
};

//=============================================================================
class AppStateManager {
	private:
		static AppState* ActiveAppState;

	public:
		static void OnEvent(SDL_Event* Event);

		static void OnLoop();

		static void OnRender();

	public:
		static void SetActiveAppState(APPSTATE AppStateID);

		static AppState* GetActiveAppState();
};

//=============================================================================

#endif
