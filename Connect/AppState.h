//=============================================================================
#ifndef __APPSTATE_H__
	#define __APPSTATE_H__

//Code from http://www.sdltutorials.com/sdl-app-states

#include "SDL.h"

#include "Event.h"

//=============================================================================
class AppState : public Event {
	public:
		AppState();

	public:
		virtual void OnActivate() = 0;

		virtual void OnDeactivate() = 0;

		virtual void OnLoop() = 0;

		virtual void OnRender() = 0;
};

//=============================================================================

#endif
