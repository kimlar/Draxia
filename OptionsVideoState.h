#pragma once

#include "State.h"

// SDL
#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "Button.h"
#include "CheckBox.h"
#include "DropList.h"

class OptionsVideoState : public State
{
public:
	OptionsVideoState();

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

	// CheckBox
	CheckBox* checkBoxFullscreen;
	CheckBox* checkBoxVSync;
	CheckBox* checkBoxFastGPU;

	// DropList
	DropList* dropListResolution;

	// Font
	ResID fontSharedBig;

	// Menu
	bool needRestartApplication;

	// Inputs
	bool keyEsc;
};
