#include "Game.h"

// Utils
#include "Utils/Debug.h"
#include "Utils/Timer.h"
#include "Utils/FpsCounter.h"

Game::Game(StateManager* stateManager) : stateManager(stateManager)
{
	resManager = stateManager->GetResourceManager();
	settings = stateManager->GetSettings();
	screen = stateManager->GetGpuTarget();
}

Game::~Game()
{
	if (resManager)
		resManager->FreeResources();
	resManager = nullptr;

	stateManager = nullptr;
	settings = nullptr;
	screen = nullptr;

	free(vertex_values);
	vertex_values = nullptr;
}

void Game::Enter()
{
	// Controls
	moveLeft = settings->GetMoveLeft(); //Controls::LEFT;
	moveUp = settings->GetMoveUp(); //Controls::UP;
	moveRight = settings->GetMoveRight(); //Controls::RIGHT;
	moveDown = settings->GetMoveDown(); //Controls::DOWN;

	//
	playerPosX = 500.0f;
	playerPosY = 500.0f;
	playerVelX = 0.0f;
	playerVelY = 0.0f;
	playerMaxSpeedX = 300.0f;
	playerMaxSpeedY = 300.0f;
	
	//
	// Load resources
	//
	
	// Font
	fontSharedBig = resManager->GetSharedFontResourceIdByName("Data\\Fonts\\OpenSans-Regular-64.fnt");
	
	// Image
	imgPlayer = resManager->GetGpuImageResourceIdByName("Data\\__General__\\spr_body_0.png");
	imgGrass = resManager->GetGpuImageResourceIdByName("Data\\__General__\\bg_grass.png");
	imgTinyHouseFloor = resManager->GetGpuImageResourceIdByName("Data\\TinyHouse\\spr_tinyhouse_floor_0.png");
	imgTinyHouseOutWest = resManager->GetGpuImageResourceIdByName("Data\\TinyHouse\\tinyhouseOutWest.png");






	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// VERT DATA
	//


	// house
	num_vertices = 3;
	floats_per_vertex = 2 + 2 + 4; // Vert(x,y) , TexCoord(s,t) , Color(r,g,b,a)
	vertex_values = (float*)malloc(sizeof(float)*num_vertices*floats_per_vertex);

	//
	// Note: PNG file is read backwards (stb png lib)
	//

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// VERT A
	//

	// Vert pos X,Y
	vertex_values[0] = 100.0f;
	vertex_values[1] = 228.0f;
	// Tex coord S,T
	if (imgTinyHouseOutWest != NULL)
	{
		vertex_values[2] = 0.0f;
		vertex_values[3] = 0.0f;
	}
	// Color RGBA
	vertex_values[4] = 255.0f;
	vertex_values[5] = 255.0f;
	vertex_values[6] = 255.0f;
	vertex_values[7] = 255.0f;

	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// VERT B
	//

	// Vert pos X,Y
	vertex_values[8] = 100.0f;
	vertex_values[9] = 100.0f;
	// Tex coord S,T
	if (imgTinyHouseOutWest != NULL)
	{
		vertex_values[10] = 0.0f;
		vertex_values[11] = 1.0f;
	}
	// Color RGBA
	vertex_values[12] = 255.0f;
	vertex_values[13] = 255.0f;
	vertex_values[14] = 255.0f;
	vertex_values[15] = 255.0f;

	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// VERT C
	//

	// Vert pos X,Y
	vertex_values[16] = 150.0f;
	vertex_values[17] = 100.0f;
	// Tex coord S,T
	if (imgTinyHouseOutWest != NULL)
	{
		vertex_values[18] = 1.0f;
		vertex_values[19] = 1.0f;
	}
	// Color RGBA
	vertex_values[20] = 255.0f;
	vertex_values[21] = 255.0f;
	vertex_values[22] = 255.0f;
	vertex_values[23] = 255.0f;

	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////







	// TIMER
	TimerStart();

	// FPS
	showFPS = settings->GetShowFps();
	lastFPS = "0";

	// State
	state = ToState::Run;
}

void Game::Exit()
{
	resManager->FreeResources();
	resManager = nullptr;
}

ToState Game::Update()
{
	// **** TIMER ****

	dt = TimerGet();


	// **** FPS COUNTER ****

	if (FpsUpdate(dt))
		lastFPS = std::to_string(FpsGet());


	// **** INPUT ****

	while (SDL_PollEvent(&e)) // e for event
	{
		if (e.type == SDL_QUIT)
			state = ToState::Quit;
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
				state = ToState::TitleMenu;
			else if (e.key.keysym.sym == SDLK_SPACE)
			{
				resManager->InsertGpuImageResource(imgPlayer, "Data\\__General__\\spr_body_1.png");
			}
			else if (e.key.keysym.sym == SDLK_RETURN)
			{
				resManager->InsertGpuImageResource(imgPlayer, "Data\\__General__\\spr_body_0.png");
			}
		}

		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			if (e.key.keysym.sym == moveUp)
				playerVelY -= playerMaxSpeedY;
			else if (e.key.keysym.sym == moveDown)
				playerVelY += playerMaxSpeedY;
			else if (e.key.keysym.sym == moveLeft)
				playerVelX -= playerMaxSpeedX;
			else if (e.key.keysym.sym == moveRight)
				playerVelX += playerMaxSpeedX;
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			if (e.key.keysym.sym == moveUp)
				playerVelY += playerMaxSpeedY;
			else if (e.key.keysym.sym == moveDown)
				playerVelY -= playerMaxSpeedY;
			else if (e.key.keysym.sym == moveLeft)
				playerVelX += playerMaxSpeedX;
			else if (e.key.keysym.sym == moveRight)
				playerVelX -= playerMaxSpeedX;
		}
	}



	// **** LOGIC ****

	playerPosX += playerVelX * (float)dt;
	playerPosY += playerVelY * (float)dt;



	// **** RENDER ****

	// Clear the screen
	GPU_Clear(screen);
	
	// Background
	Uint16 iw = resManager->GetGpuImageResource(imgGrass)->GetGpuImage()->w;
	Uint16 ih = resManager->GetGpuImageResource(imgGrass)->GetGpuImage()->h;
	Uint16 iw2 = resManager->GetGpuImageResource(imgGrass)->GetGpuImage()->w / 2;
	Uint16 ih2 = resManager->GetGpuImageResource(imgGrass)->GetGpuImage()->h / 2;
	for (unsigned int y = 0; y < 17; ++y)
	{
		for (unsigned int x = 0; x < 30; ++x)
		{
			resManager->GetGpuImageResource(imgGrass)->DrawImage((float)x * iw + iw2, (float)y * ih + ih2);
		}
	}


	// House

	// Floor

	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(400.0f, 400.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(500.0f, 400.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(600.0f, 400.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(700.0f, 400.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(800.0f, 400.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(900.0f, 400.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(400.0f, 500.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(500.0f, 500.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(600.0f, 500.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(700.0f, 500.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(800.0f, 500.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(900.0f, 500.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(400.0f, 600.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(500.0f, 600.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(600.0f, 600.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(700.0f, 600.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(800.0f, 600.0f);
	resManager->GetGpuImageResource(imgTinyHouseFloor)->DrawImage(900.0f, 600.0f);
	
	// Text
	resManager->GetSharedFontResource(fontSharedBig)->DrawText("Testing", 300.0f, 400.0f);

	// Draw triangle batch
	GPU_TriangleBatch(resManager->GetGpuImageResource(imgTinyHouseOutWest)->GetGpuImage(), screen, num_vertices, vertex_values, 0, NULL, GPU_BATCH_XY_ST_RGBA);

	// Player
	resManager->GetGpuImageResource(imgPlayer)->DrawImage(playerPosX, playerPosY);
	
	// Draw FPS
	if (showFPS)
		resManager->GetSharedFontResource(fontSharedBig)->DrawText("FPS: " + lastFPS, 20.0f, 32.0f);

	// Show the result in the window
	GPU_Flip(screen);
	
	return state;
}
