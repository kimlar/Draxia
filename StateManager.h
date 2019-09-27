#pragma once

#include "State.h"

// SDL
//#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "Settings.h"
#include "ResourceManager.h"
//#include "Font.h"


class State;

class StateManager
{
public:
	StateManager();
	~StateManager();

	void Free();

	// Manage states
	void AddState(State* state);
	void RemoveState();
	void ReplaceState(State* state);
	int Update();

	State* GetState();

	// Special operations
	void SetGpuTarget(GPU_Target* screen);
	GPU_Target* GetGpuTarget();

	void SetResourceManager(ResourceManager* resManager);
	ResourceManager* GetResourceManager();

	void SetSettings(Settings* settings);
	Settings* GetSettings();
	void ReadSettings();
	void WriteSettings();

private:
	std::vector<State*> vState;
	State* curState;
	
	GPU_Target* screen;
	ResourceManager* resManager;
	Settings* settings;
};
