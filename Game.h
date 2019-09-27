#pragma once

// SDL
#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "ResourceManager.h"
#include "StateManager.h"
#include "Font.h"

class Game
{
public:
	Game(StateManager* stateManager);
	virtual ~Game();

	void Enter();
	void Exit();
	ToState Update();

private:
	ResourceManager *resManager;
	StateManager* stateManager;
	Settings* settings;
	GPU_Target* screen;
	SDL_Event e; // e for event

	// State
	ToState state;

	// TIMER
	double dt; // delta time

	// FPS
	bool showFPS;
	std::string lastFPS;
	
	//
	// Game
	//

	// Font
	ResID fontSharedBig;

	// Image
	ResID imgPlayer;
	ResID imgGrass;
	ResID imgTinyHouseFloor;
	ResID imgTinyHouseOutWest;

	// Controls
	int moveLeft;
	int moveUp;
	int moveRight;
	int moveDown;

	//
	float playerPosX;
	float playerPosY;
	float playerVelX;
	float playerVelY;
	float playerMaxSpeedX;
	float playerMaxSpeedY;

	// house
	int num_vertices;
	int floats_per_vertex; // Vert(x,y) , TexCoord(s,t) , Color(r,g,b,a)
	float* vertex_values;
};
