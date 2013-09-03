#ifndef _APP_H_
#define _APP_H_

#include "SDL_Image.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <ctime>
#include "Constants.h"
#include "Event.h"
#include "FileNames.h"
#include "AppStateManager.h"

class App : public Event {
public:
	App();
	bool init();
	int execute();
	void input(SDL_Event* Events);
		void OnExit();
	void loop();
	void render();
	void free();
private:
	bool running;
	static const int SCREEN_BPP = 32;
	SDL_Surface* icon;
	bool loadIcon();
};

#endif
