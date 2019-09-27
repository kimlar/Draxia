#pragma once

// SDL
#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "StateManager.h"
#include "ResourceManager.h"

class Slider
{
public:
	Slider(StateManager* stateManager, ResID fontResID, std::string text, float x, float y, bool sharedFont = false);
	virtual ~Slider();

	void Free();
	void Draw();
	void Event(SDL_Event &e);

	enum class SliderEventState
	{
		Up = 0,
		Down,
		Hover,
	};

	void SetEvent(SliderEventState seState);
	SliderEventState GetEvent();

	void SetClick(bool click);
	bool GetClick();

	void SetValue(int value);
	int GetValue();
	
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
	float rx;
	float ry;
	float rw;
	float rh;
	float bx;
	float by;
	float bw;
	float bh;
	std::string text;

	SDL_Color edgeLightColor;
	SDL_Color edgeDarkColor;
	SDL_Color fillColor;
	SDL_Color hoverColor;
	SDL_Color textColor;
	SDL_Color railColor;
	SDL_Color valueColor;

	SliderEventState sliderEventState;
	bool click;
	bool drag;

	int sliderValue;
	//int sliderMin;
	//int sliderMax;
};
