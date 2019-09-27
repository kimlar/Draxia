#pragma once

// SDL
#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "StateManager.h"
#include "ResourceManager.h"

class CheckBox
{
public:
	CheckBox(StateManager* stateManager, ResID fontResID, std::string text, float x, float y, bool sharedFont = false);
	virtual ~CheckBox();

	void Free();
	void Draw();
	void Event(SDL_Event &e);

	enum class CheckBoxEventState
	{
		Up = 0,
		Down,
		Hover,
	};

	void SetEvent(CheckBoxEventState cbeState);
	CheckBoxEventState GetEvent();

	void SetClick(bool click);
	bool GetClick();

	void SetOn(bool on);

private:
	StateManager* stateManager;
	ResourceManager* resManager;
	GPU_Target* screen;

	// Font
	ResID fontResID;
	bool sharedFont;

	// General
	float x;
	float y;
	float width;
	float height;
	float cbx;
	float cby;
	float cbw;
	float cbh;
	std::string text;

	SDL_Color edgeLightColor;
	SDL_Color edgeDarkColor;
	SDL_Color fillColor;
	SDL_Color onColor;
	SDL_Color hoverColor;
	SDL_Color textColor;

	CheckBoxEventState checkBoxEventState;
	bool click;
	bool on;
};
