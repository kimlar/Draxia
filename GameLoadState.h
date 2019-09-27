#pragma once

#include "State.h"

class GameLoadState : public State
{
public:
	GameLoadState();
	virtual ~GameLoadState();

	void Enter();
	void Exit();
	GotoState Update();

private:
	StateManager* stateManager;
	ResourceManager* resManager;

	// Font
	ResID fontSharedBig;
};
