#pragma once

#include "State.h"

class InitAppState : public State
{
public:
	InitAppState();

	void Enter();
	void Exit();
	GotoState Update();

private:
	StateManager* stateManager;
	ResourceManager *resManager;
	Settings* settings;
	GPU_Target* screen;

	// Font
	ResID fontSharedBig;

};