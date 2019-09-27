#pragma once

// SDL
#include "SDL.h"
#include "SDL_gpu.h"


// Project
#include "ResourceManager.h"
#include "StateManager.h"
#include "Font.h"
#include "Button.h"

// State
#include "State.h"

class TitleMenuState : public State
{
public:
	TitleMenuState();

	void Enter();
	void Exit();
	GotoState Update();

private:
	StateManager* stateManager;
	ResourceManager *resManager;
	GPU_Target* screen;
	SDL_Event e; // e for event

	// Button
	Button* buttonNewGame;
	Button* buttonOptions;
	Button* buttonExit;

	// Font
	ResID fontSharedBig;

	// Inputs
	//bool keyEsc;
};
