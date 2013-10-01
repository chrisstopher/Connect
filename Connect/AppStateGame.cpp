//Code from http://www.sdltutorials.com/sdl-app-states
//Modified to what I needed on my game

//=============================================================================
#include "AppStateGame.h"

#include "AppStateManager.h"

//=============================================================================
AppStateGame AppStateGame::Instance;

//=============================================================================
AppStateGame::AppStateGame() : connect(NULL), gui(NULL) {
	
}

//=============================================================================
void AppStateGame::OnActivate() {
	std::ifstream file(GAME_PARAMETERS);
	if (!file) {
		std::cout << "Could not open " << GAME_PARAMETERS << ".\n";
		AppStateManager::SetActiveAppState(APPSTATE_NONE);
		return;
	}
	//int playerCount, timeLimit, connectCount, rowCount columnCount;
	int args[5] = {-1};
	for (int i = 0; i < 5; i++) {
		file >> args[i];
	}
	Timer* timer;
	switch (args[1]) {
		case 0:
			timer = new NoTimer();
			break;
		default:
			timer = new Timer(args[1]);
			break;

	}
	connect = new Connect(args[0], timer, args[2], args[3], args[4]);
	file.close();
	if (!connect->load()) {
		std::cout << "Could not load connect.\n";
		AppStateManager::SetActiveAppState(APPSTATE_NONE);
		return;
	}
	gui = new GUIObjectManager();
	if (!gui->load(GUI_GAME)) {
		std::cout << "Could not load " << GUI_GAME << ".\n";
		AppStateManager::SetActiveAppState(APPSTATE_NONE);
		return;
	}
}

void AppStateGame::OnLButtonUp(int mX, int mY) {
	connect->onClick(mX, mY);
	if (connect->gameIsOver() && connect->allPlayersLastCheckerInPlace()) {
		int changed = gui->onClick(mX, mY);
		switch ((GUIObjectManager::OBJECT_CHANGES)changed) {
			case GUIObjectManager::STATE:
				AppStateManager::SetActiveAppState(APPSTATE_MENU);
			break;
			case GUIObjectManager::RESET:
				connect->startOver();
			break;
			case GUIObjectManager::PLAY_AGAIN:
				connect->dropCheckers();
			break;
			default:
			break;
		}
	}
}

void AppStateGame::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
	connect->onMouseMove(mX, mY, relX, relY, Left, Right, Middle);
}

void AppStateGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym) {
		case SDLK_a:
		case SDLK_SPACE:
			connect->dropCheckers();
			break;
		case SDLK_r:
			connect->startOver();
			break;
		case SDLK_ESCAPE:
		case SDLK_b:
			if (connect->gameIsOver() && connect->allPlayersLastCheckerInPlace()) {
				AppStateManager::SetActiveAppState(APPSTATE_MENU);
			}
			break;
		default:
			break;
	}
}

//-----------------------------------------------------------------------------
void AppStateGame::OnLoop() {
	connect->logic();
}

//-----------------------------------------------------------------------------
void AppStateGame::OnRender() {
	connect->draw();
	if (connect->gameIsOver() && connect->allPlayersLastCheckerInPlace()) {
		gui->draw();
	}
}

//-----------------------------------------------------------------------------
void AppStateGame::OnDeactivate() {
	if (connect) {
		connect->free();
		delete connect;
	}
	if (gui) {
		gui->free();
		delete gui;
	}
}

//=============================================================================
AppStateGame* AppStateGame::GetInstance() {
	return &Instance;
}

//=============================================================================
