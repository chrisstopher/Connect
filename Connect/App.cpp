#include "App.h"

App::App() : running(true), icon(NULL) {

}
/*
Initializing everything
Setting the appl state to menu
*/
bool App::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!loadIcon()) {
		return false;
	}
	SDL_WM_SetIcon(icon, NULL);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_WM_SetCaption("Connect", NULL);
	SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL);
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	srand(static_cast<unsigned>(time(NULL)));
	AppStateManager::SetActiveAppState(APPSTATE_MENU);
	return true;
}

bool App::loadIcon() {
	icon = IMG_Load(APP_ICON);
	if (!icon) {
		std::cout << "Could not load: " << APP_ICON << "\n";
		return false;
	}
	return true;
}

void App::input(SDL_Event* Events) {
	Event::OnEvent(Events);
	AppStateManager::OnEvent(Events);
}

void App::OnExit() {
	running = false;
}

void App::loop() {
	if (!AppStateManager::GetActiveAppState()) {
		running = false;
	}
	AppStateManager::OnLoop();
}

void App::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
	AppStateManager::OnRender();
	SDL_GL_SwapBuffers();
}

void App::free() {
	AppStateManager::SetActiveAppState(APPSTATE_NONE);
	SDL_FreeSurface(icon);
	SDL_Quit();
}

int App::execute() {
	if (!init()) {
		return 1;
	}
	SDL_Event Event;
	while (running) {
		while (SDL_PollEvent(&Event)) {
			input(&Event);
		}
		loop();
		render();
		SDL_Delay(20);
	}
	free();
	return 0;
}
