#include "StateManager.h"

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
	Free();
}

void StateManager::Free()
{
	if (curState)
	{
		for (int i = (int)vState.size() - 1; i > 0; i--)
			vState[i]->Exit();
		vState.clear();

		if (curState)
			delete curState;
		curState = nullptr;

		if (resManager)
		{
			resManager->FreeResources();
			resManager->FreeSharedResources();
			delete resManager;
		}
		resManager = nullptr;

		screen = nullptr;

		if (settings)
			delete settings;
		settings = nullptr;
	}
}

void StateManager::AddState(State* state)
{
	// Exit state
	if (!vState.empty())
	{
		vState.back()->Exit();
		curState = nullptr;
	}

	// Add state
	vState.push_back(state);
	
	// Enter state
	curState = vState.back();
	curState->SetStateManager(this); // Store the state manager
	curState->Enter();
}

void StateManager::RemoveState()
{
	// Exit state
	if (!vState.empty())
	{
		vState.back()->Exit();
		curState = nullptr;
	}

	// Remove state
	if (!vState.empty())
		vState.pop_back();

	// Enter state
	if (!vState.empty())
	{
		curState = vState.back();
		curState->Enter();
	}
}

void StateManager::ReplaceState(State* state)
{
	// Exit state
	if (!vState.empty())
	{
		vState.back()->Exit();
		curState = nullptr;

		// Remove state
		vState.pop_back();
	}

	// Add state
	vState.push_back(state);

	// Enter state
	curState = vState.back();
	curState->SetStateManager(this); // Store the state manager
	curState->Enter();

}

int StateManager::Update()
{
	return curState->Update();
}

State* StateManager::GetState()
{
	return curState;
}

void StateManager::SetGpuTarget(GPU_Target* screen)
{
	this->screen = screen;
}

GPU_Target* StateManager::GetGpuTarget()
{
	return screen;
}

void StateManager::SetResourceManager(ResourceManager* resManager)
{
	this->resManager = resManager;
}

ResourceManager* StateManager::GetResourceManager()
{
	return resManager;
}

void StateManager::SetSettings(Settings* settings)
{
	this->settings = settings;
}

Settings* StateManager::GetSettings()
{
	return settings;
}

void StateManager::ReadSettings()
{
	if (settings)
	{
		delete settings;
	}
	

	settings = new Settings();
	settings->Load();
}

void StateManager::WriteSettings()
{
	if (settings)
	{
		settings->Save();
	}
}
