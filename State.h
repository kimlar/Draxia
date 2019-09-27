#pragma once

#include "StateManager.h"

typedef enum _GotoState
{
	Run = 0,
	Quit,
	InitApp,
	TitleMenu,
	GameLoad,
	GamePlay,
	Options,
	OptionsVideo,
	OptionsSound,
	OptionsGame,
	OptionsControls,
} ToState;

using GotoState = int;
using StateName = std::string;

class StateManager;

class State
{
public:
	State();
	virtual ~State();

	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual GotoState Update() = 0;

	void SetStateManager(StateManager* stateManager);
	StateManager* GetStateManager();

	//void SetStateName(StateName stateName);
	StateName GetStateName();
	
protected:
	StateName stateName;

private:
	StateManager* stateManager;
};
