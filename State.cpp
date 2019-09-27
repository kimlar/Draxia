#include "State.h"

State::State()
{
}

State::~State()
{
	stateManager = nullptr;
}

void State::SetStateManager(StateManager* stateManager)
{
	this->stateManager = stateManager;
}

StateManager* State::GetStateManager()
{
	return stateManager;
}

/*
void State::SetStateName(StateName stateName)
{
	this->stateName = stateName;
}
*/
StateName State::GetStateName()
{
	return stateName;
}
