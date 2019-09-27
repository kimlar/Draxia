#include "GamePlayState.h"


GamePlayState::GamePlayState()
{
	stateName = "GamePlay";
}

GamePlayState::~GamePlayState()
{
	if (game)
	{
		game->Exit();
		delete game;
	}
	game = nullptr;
}

void GamePlayState::Enter()
{
	game = new Game(this->GetStateManager());
	game->Enter();
}

void GamePlayState::Exit()
{
	game->Exit();
	if (game)
		delete game;
	game = nullptr;
}

GotoState GamePlayState::Update()
{
	return game->Update();
}
