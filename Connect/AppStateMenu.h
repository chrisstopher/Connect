//=============================================================================
#ifndef __APPSTATEMENU_H__
	#define __APPSTATEMENU_H__

//Code from http://www.sdltutorials.com/sdl-app-states
//Modified to what I needed on my menu

#include "AppState.h"
#include "GUIObjectManager.h"

//=============================================================================
class AppStateMenu : public AppState {
	private:
		static AppStateMenu Instance;

	private:
		AppStateMenu();

		GUIObjectManager* gui;

	public:
		virtual void OnActivate();

		virtual void OnDeactivate();

			void OnLButtonUp(int mX, int mY);

			void OnMouseWheel(bool Up, bool Down, int mX, int mY);

			void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

		virtual void OnLoop();

		virtual void OnRender();

	public:
		static AppStateMenu* GetInstance();
};

//=============================================================================

#endif
