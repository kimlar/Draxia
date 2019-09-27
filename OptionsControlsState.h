#pragma once

#include "State.h"

// SDL
#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "Controls.h"
#include "Button.h"
#include "EditBox.h"

class OptionsControlsState : public State
{
public:
	OptionsControlsState();

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
	Button* buttonSave;
	Button* buttonBack;

	// EditBox
	EditBox* editBoxMoveLeft;
	EditBox* editBoxMoveUp;
	EditBox* editBoxMoveRight;
	EditBox* editBoxMoveDown;

	// Font
	ResID fontSharedBig;

	// Menu
	bool selectKey;
	int selectEditBox;

	// Inputs
	bool keyEsc;
};
