#include "OptionsState.h"
#include "EditBox.h"



OptionsState::OptionsState()
{
	stateName = "Options";
}

void OptionsState::Enter()
{
	stateManager = this->GetStateManager();
	resManager = stateManager->GetResourceManager();
	screen = stateManager->GetGpuTarget();
	settings = stateManager->GetSettings();

	//
	// Load resources
	//

	// Font
	//fontSharedBig = resManager->AddSharedFontResource("Data\\Fonts\\OpenSans-Regular-64.fnt");
	fontSharedBig = resManager->GetSharedFontResourceIdByName("Data\\Fonts\\OpenSans-Regular-64.fnt");

	// Button
	buttonVideoOptions = new Button(stateManager, fontSharedBig, "Video", 500.0f, 300.0f, true);
	buttonSoundOptions = new Button(stateManager, fontSharedBig, "Sound", 500.0f, 400.0f, true);
	buttonGameOptions = new Button(stateManager, fontSharedBig, "Game", 500.0f, 500.0f, true);
	buttonControls = new Button(stateManager, fontSharedBig, "Controls", 500.0f, 600.0f, true);
	buttonBack = new Button(stateManager, fontSharedBig, "Back", 500.0f, 700.0f, true);

	// Keyboard
	keyEsc = false;
}

void OptionsState::Exit()
{
	resManager->FreeResources();
	fontSharedBig = 0;
	
	if (buttonVideoOptions)
		delete buttonVideoOptions;
	buttonVideoOptions = nullptr;

	if (buttonSoundOptions)
		delete buttonSoundOptions;
	buttonSoundOptions = nullptr;

	if (buttonGameOptions)
		delete buttonGameOptions;
	buttonGameOptions = nullptr;

	if (buttonControls)
		delete buttonControls;
	buttonControls = nullptr;

	if (buttonBack)
		delete buttonBack;
	buttonBack = nullptr;

	resManager = nullptr;
	stateManager = nullptr;
	settings = nullptr;
	screen = nullptr;
}

GotoState OptionsState::Update()
{
	// **** INPUT ****

	while (SDL_PollEvent(&e)) // e for event
	{
		if (e.type == SDL_QUIT)
		{
			return ToState::Quit;
		}		
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				if (keyEsc)
					break;
				keyEsc = true;

				return ToState::TitleMenu;
			}
		}
		else if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				keyEsc = false;
				break;
			}
		}
		
		// Check "Video"
		buttonVideoOptions->Event(e);
		if (buttonVideoOptions->GetClick())
		{
			buttonVideoOptions->SetClick(false);

			//menuSelection = 0;
			return ToState::OptionsVideo;
		}
		// Check "Sound"
		buttonSoundOptions->Event(e);
		if (buttonSoundOptions->GetClick())
		{
			buttonSoundOptions->SetClick(false);

			//menuSelection = 0;
			return ToState::OptionsSound;
		}
		// Check "Game"
		buttonGameOptions->Event(e);
		if (buttonGameOptions->GetClick())
		{
			buttonGameOptions->SetClick(false);

			//menuSelection = 0;
			return ToState::OptionsGame;
		}
		// Check "Controls"
		buttonControls->Event(e);
		if (buttonControls->GetClick())
		{
			buttonControls->SetClick(false);

			//menuSelection = 0;
			return ToState::OptionsControls;
		}
		// Check "Back"
		buttonBack->Event(e);
		if (buttonBack->GetClick())
		{
			buttonBack->SetClick(false);

			//menuSelection = 0;
			return ToState::TitleMenu;
		}

	}
	

	// **** RENDER ****

	// Clear the screen
	GPU_Clear(screen);

	//
	resManager->GetSharedFontResource(fontSharedBig)->SetColor(160, 160, 160, 255);
	resManager->GetSharedFontResource(fontSharedBig)->DrawText("OPTIONS", 500.0f, 200.0f);

	// Buttons
	buttonVideoOptions->Draw();
	buttonSoundOptions->Draw();
	buttonGameOptions->Draw();
	buttonControls->Draw();
	buttonBack->Draw();

	// Show the result in the window
	GPU_Flip(screen);
	
	return ToState::Run;
}
