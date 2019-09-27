#pragma once

#include "State.h"

// SDL
#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "Button.h"
#include "Slider.h"

class OptionsSoundState : public State
{
public:
	OptionsSoundState();

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

	// Slider
	Slider* sliderMasterVolume;
	Slider* sliderVoiceVolume;
	Slider* sliderSfxVolume;
	Slider* sliderMusicVolume;

	// Font
	ResID fontSharedBig;

	// Inputs
	bool keyEsc;
};
