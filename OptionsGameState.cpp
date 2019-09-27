#include "OptionsGameState.h"



OptionsGameState::OptionsGameState()
{
	stateName = "OptionsGame";
}

void OptionsGameState::Enter()
{
	stateManager = this->GetStateManager();
	resManager = stateManager->GetResourceManager();
	screen = stateManager->GetGpuTarget();
	settings = stateManager->GetSettings();

	//
	// Load resources
	//

	// Font
	fontSharedBig = resManager->GetFontResourceIdByName("Data\\Fonts\\OpenSans-Regular-64.fnt");

	// Button
	buttonSave = new Button(stateManager, fontSharedBig, "Save", 500.0f, 400.0f, true);
	buttonBack = new Button(stateManager, fontSharedBig, "Back", 500.0f, 500.0f, true);

	// CheckBox
	checkBoxShowFPS = new CheckBox(stateManager, fontSharedBig, "Show FPS", 500.0f, 300.0f, true);
	checkBoxShowFPS->SetOn(settings->GetShowFps());

	// Keyboard
	keyEsc = false;
}

void OptionsGameState::Exit()
{
	resManager->FreeResources();
	fontSharedBig = 0;

	if (checkBoxShowFPS)
		delete checkBoxShowFPS;
	checkBoxShowFPS = nullptr;

	if (buttonSave)
		delete buttonSave;
	buttonSave = nullptr;

	if (buttonBack)
		delete buttonBack;
	buttonBack = nullptr;

	resManager = nullptr;
	stateManager = nullptr;
	settings = nullptr;
	screen = nullptr;
}

GotoState OptionsGameState::Update()
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

				return ToState::Options;
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

		// Check "Show FPS"
		checkBoxShowFPS->Event(e);
		if (checkBoxShowFPS->GetClick())
		{
			checkBoxShowFPS->SetClick(false);

			settings->SetShowFps(!settings->GetShowFps());
		}
		// Check "Save"
		buttonSave->Event(e);
		if (buttonSave->GetClick())
		{
			buttonSave->SetClick(false);

			// Write to file
			settings->Save();
		}
		// Check "Back"
		buttonBack->Event(e);
		if (buttonBack->GetClick())
		{
			buttonBack->SetClick(false);

			return ToState::Options;
		}
	}
	

	// **** RENDER ****

	// Clear the screen
	GPU_Clear(screen);

	//
	resManager->GetSharedFontResource(fontSharedBig)->SetColor(160, 160, 160, 255);
	resManager->GetSharedFontResource(fontSharedBig)->DrawText("GAME OPTIONS", 500.0f, 200.0f);

	// Button
	buttonSave->Draw();
	buttonBack->Draw();

	// CheckBox
	checkBoxShowFPS->Draw();

	// Show the result in the window
	GPU_Flip(screen);
	
	return ToState::Run;
}
