//=============================================================================
#ifndef __APPSTATEGAME_H__
	#define __APPSTATEGAME_H__

//Code from http://www.sdltutorials.com/sdl-app-states
//Modified to what I needed on my game

#include "AppState.h"
#include <fstream>
#include "Connect.h"
#include "GUIObjectManager.h"
#include "FileNames.h"
#include "Lua.h"

//=============================================================================
class AppStateGame : public AppState {
	private:
		static AppStateGame Instance;

	private:
		AppStateGame();

		Connect* connect;
		GUIObjectManager* gui;

	public:
		virtual void OnActivate();

		virtual void OnDeactivate();
		
			void OnLButtonUp(int mX, int mY);
			void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

		virtual void OnLoop();

		virtual void OnRender();

	public:
		static AppStateGame* GetInstance();
};

//=============================================================================

#endif
