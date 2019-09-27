#pragma once

#include "State.h"

// SDL
#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "Button.h"

class OptionsState : public State
{
public:
	OptionsState();

	void Enter();
	void Exit();
	GotoState Update();

private:
	StateManager* stateManager;
	ResourceManager *resManager;
	Settings* settings;
	GPU_Target* screen;
	SDL_Event e; // e for event
	
	// Button
	Button* buttonVideoOptions;
	Button* buttonSoundOptions;
	Button* buttonGameOptions;
	Button* buttonControls;
	Button* buttonBack;

	// Font
	ResID fontSharedBig;

	// Keyboard
	bool keyEsc;
};
