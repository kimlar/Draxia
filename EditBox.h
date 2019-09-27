#pragma once

// SDL
#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "StateManager.h"
#include "ResourceManager.h"

class EditBox
{
public:
	EditBox(StateManager* stateManager, ResID fontResID, std::string label, float x, float y, bool sharedFont = false);
	virtual ~EditBox();

	void Free();
	void Draw();
	void Event(SDL_Event &e);

	enum class EditBoxEventState
	{
		Up = 0,
		Down,
		Hover,
	};

	void SetEvent(EditBoxEventState ebeState);
	EditBoxEventState GetEvent();

	void SetClick(bool click);
	bool GetClick();

	void SetInput(std::string input);
	std::string GetInput();

	void SetInputColor(SDL_Color color);

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
	float ex;
	float ey;
	float ew;
	float eh;
	float tx;
	float ty;
	float width;
	float height;
	std::string label;
	std::string input;

	SDL_Color edgeLightColor;
	SDL_Color edgeDarkColor;
	SDL_Color fillColor;
	SDL_Color hoverColor;
	SDL_Color textColor;
	SDL_Color inputColor;

	EditBoxEventState editBoxEventState;
	bool click;
};
