#pragma once

// SDL
#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "StateManager.h"
#include "ResourceManager.h"

class Button
{
public:
	Button(StateManager* stateManager, ResID fontResID, std::string text, float x, float y, bool sharedFont = false);
	virtual ~Button();

	void Free();
	void Draw();
	void Event(SDL_Event &e);

	enum class ButtonEventState
	{
		Up = 0,
		Down,
		Hover,
	};

	void SetEvent(ButtonEventState beState);
	ButtonEventState GetEvent();

	void SetClick(bool click);
	bool GetClick();

private:
	StateManager* stateManager;
	ResourceManager* resManager;
	GPU_Target* screen;

	// Font
	ResID fontResID;
	bool sharedFont;

	// General
	float xDown;
	float yDown;
	float x;
	float y;
	float width;
	float height;
	std::string text;

	SDL_Color edgeLightColor;
	SDL_Color edgeDarkColor;
	SDL_Color fillColor;
	SDL_Color hoverColor;
	SDL_Color textColor;

	ButtonEventState buttonEventState;
	bool click;
};
