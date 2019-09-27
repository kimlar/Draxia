#pragma once

#include "State.h"
#include "Game.h"

class GamePlayState : public State
{
public:
	GamePlayState();
	virtual ~GamePlayState();

	void Enter();
	void Exit();
	GotoState Update();

private:
	Game* game;
};
