#include "TitleMenuState.h"


TitleMenuState::TitleMenuState()
{
	stateName = "TitleMenu";
}

void TitleMenuState::Enter()
{
	stateManager = this->GetStateManager();
	resManager = stateManager->GetResourceManager();
	screen = stateManager->GetGpuTarget();

	//
	// Load resources
	//

	// Font
	fontSharedBig = resManager->GetSharedFontResourceIdByName("Data\\Fonts\\OpenSans-Regular-64.fnt");

	// Button
	buttonNewGame = new Button(stateManager, fontSharedBig, "New Game", 500.0f, 300.0f, true);
	buttonOptions = new Button(stateManager, fontSharedBig, "Options", 500.0f, 400.0f, true);
	buttonExit = new Button(stateManager, fontSharedBig, "Exit", 500.0f, 500.0f, true);

	//
	// Inputs
	//
	//keyEsc = false;
}

void TitleMenuState::Exit()
{
	resManager->FreeResources();
	fontSharedBig = 0;

	if (buttonNewGame)
		delete buttonNewGame;
	buttonNewGame = nullptr;

	if (buttonOptions)
		delete buttonOptions;
	buttonOptions = nullptr;

	if (buttonExit)
		delete buttonExit;
	buttonExit = nullptr;


	resManager = nullptr;
	stateManager = nullptr;
	screen = nullptr;
}

GotoState TitleMenuState::Update()
{
	// **** INPUT ****

	while (SDL_PollEvent(&e)) // e for event
	{
		if (e.type == SDL_QUIT)
		{
			return ToState::Quit;
		}
		// Check "New Game"
		buttonNewGame->Event(e);
		if (buttonNewGame->GetClick())
		{
			//menuSelection = 0;
			return ToState::GameLoad;
		}
		// Check "Options"
		buttonOptions->Event(e);
		if (buttonOptions->GetClick())
		{
			//menuSelection = 0;
			return ToState::Options;
		}
		// Check "Exit"
		buttonExit->Event(e);
		if (buttonExit->GetClick())
		{
			//menuSelection = 0;
			return ToState::Quit;
		}

	}


	// **** RENDER ****

	// Clear the screen
	GPU_Clear(screen);

	//
	resManager->GetSharedFontResource(fontSharedBig)->SetColor(160, 160, 160, 255);
	resManager->GetSharedFontResource(fontSharedBig)->DrawText("TITLE MENU", 500.0f, 200.0f);

	// Buttons
	buttonNewGame->Draw();
	buttonOptions->Draw();
	buttonExit->Draw();

	// Show the result in the window
	GPU_Flip(screen);
	
	return ToState::Run;
}
