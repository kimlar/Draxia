#pragma once

// SDL
#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "StateManager.h"
#include "ResourceManager.h"

class DropList
{
public:
	DropList(StateManager* stateManager, ResID fontResID, std::string label, float x, float y, bool sharedFont = false);
	virtual ~DropList();

	void Free();
	void Draw();
	void Event(SDL_Event &e);

	enum class DropListEventState
	{
		Up = 0,
		Down,
	};

	void SetEvent(DropListEventState dleState);
	DropListEventState GetEvent();

	void SetClick(bool click);
	bool GetClick();

	void SetShowList(bool show);
	bool GetShowList();
	bool EscIsPressed();

	void AddItem(std::string item);

	void SetItemSelectedByText(std::string ItemText);
	std::string GetItemSelected();

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
	float dlx;
	float dly;
	float dlw;
	float dlh;
	float btx;
	float bty;
	float btw;
	float bth;
	std::string label;
	std::string text;

	SDL_Color edgeLightColor;
	SDL_Color edgeDarkColor;
	SDL_Color fillColor;
	SDL_Color hoverColor;
	SDL_Color labelColor;
	SDL_Color listColor;
	SDL_Color listSelectionColor;

	DropListEventState dropListEventState;
	bool click;
	bool showList;
	int vListItemSelected;
	std::vector<std::string> vList;

	// Mouse stuff
	int mx;
	int my;
	int mouseHoverSelect;
};
