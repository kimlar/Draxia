#include "OptionsControlsState.h"

OptionsControlsState::OptionsControlsState()
{
	stateName = "OptionsControls";
}

void OptionsControlsState::Enter()
{
	stateManager = this->GetStateManager();
	resManager = stateManager->GetResourceManager();
	screen = stateManager->GetGpuTarget();
	settings = stateManager->GetSettings();

	//
	// Load resources
	//

	// Font
	fontSharedBig = resManager->GetSharedFontResourceIdByName("Data\\Fonts\\OpenSans-Regular-64.fnt");

	// Button
	buttonSave = new Button(stateManager, fontSharedBig, "Save", 500.0f, 700.0f, true);
	buttonBack = new Button(stateManager, fontSharedBig, "Back", 500.0f, 800.0f, true);

	// EditBox
	editBoxMoveLeft = new EditBox(stateManager, fontSharedBig, "Move Left", 500.0f, 300.0f, true);
	editBoxMoveLeft->SetInput(GetKeyByValue(settings->GetMoveLeft()));
	editBoxMoveUp = new EditBox(stateManager, fontSharedBig, "Move Up", 500.0f, 400.0f, true);
	editBoxMoveUp->SetInput(GetKeyByValue(settings->GetMoveUp()));
	editBoxMoveRight = new EditBox(stateManager, fontSharedBig, "Move Right", 500.0f, 500.0f, true);
	editBoxMoveRight->SetInput(GetKeyByValue(settings->GetMoveRight()));
	editBoxMoveDown = new EditBox(stateManager, fontSharedBig, "Move Down", 500.0f, 600.0f, true);
	editBoxMoveDown->SetInput(GetKeyByValue(settings->GetMoveDown()));

	//
	// Inputs
	//
	keyEsc = false;

	//
	selectKey = false;
	selectEditBox = -1; // No selected edit box
}

void OptionsControlsState::Exit()
{
	resManager->FreeResources();
	fontSharedBig = 0;

	if (editBoxMoveLeft)
		delete editBoxMoveLeft;
	editBoxMoveLeft = nullptr;

	if (editBoxMoveUp)
		delete editBoxMoveUp;
	editBoxMoveUp = nullptr;

	if (editBoxMoveRight)
		delete editBoxMoveRight;
	editBoxMoveRight = nullptr;

	if (editBoxMoveDown)
		delete editBoxMoveDown;
	editBoxMoveDown = nullptr;

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

GotoState OptionsControlsState::Update()
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
			if (selectKey)
			{
				switch (selectEditBox)
				{
				case 0:
					editBoxMoveLeft->SetInputColor({ 255, 255, 255, 255 });
					settings->SetMoveLeft(e.key.keysym.sym);
					editBoxMoveLeft->SetInput(GetKeyByValue(settings->GetMoveLeft()));
					break;
				case 1:
					editBoxMoveUp->SetInputColor({ 255, 255, 255, 255 });
					settings->SetMoveUp(e.key.keysym.sym);
					editBoxMoveUp->SetInput(GetKeyByValue(settings->GetMoveUp()));
					break;
				case 2:
					editBoxMoveRight->SetInputColor({ 255, 255, 255, 255 });
					settings->SetMoveRight(e.key.keysym.sym);
					editBoxMoveRight->SetInput(GetKeyByValue(settings->GetMoveRight()));
					break;
				case 3:
					editBoxMoveDown->SetInputColor({ 255, 255, 255, 255 });
					settings->SetMoveDown(e.key.keysym.sym);
					editBoxMoveDown->SetInput(GetKeyByValue(settings->GetMoveDown()));
					break;
				}
				selectKey = false;
				selectEditBox = -1;
			}
			else
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

		// Check "Move Left"
		editBoxMoveLeft->Event(e);
		if (editBoxMoveLeft->GetClick())
		{
			editBoxMoveLeft->SetClick(false);

			editBoxMoveLeft->SetInputColor({ 255, 255, 0, 255 });
			editBoxMoveLeft->SetInput("Press key");

			selectKey = true;
			selectEditBox = 0;
		}
		// Check "Move Up"
		editBoxMoveUp->Event(e);
		if (editBoxMoveUp->GetClick())
		{
			editBoxMoveUp->SetClick(false);

			editBoxMoveUp->SetInputColor({ 255, 255, 0, 255 });
			editBoxMoveUp->SetInput("Press key");

			selectKey = true;
			selectEditBox = 1;
		}
		// Check "Move Right"
		editBoxMoveRight->Event(e);
		if (editBoxMoveRight->GetClick())
		{
			editBoxMoveRight->SetClick(false);

			editBoxMoveRight->SetInputColor({ 255, 255, 0, 255 });
			editBoxMoveRight->SetInput("Press key");

			selectKey = true;
			selectEditBox = 2;
		}
		// Check "Move Down"
		editBoxMoveDown->Event(e);
		if (editBoxMoveDown->GetClick())
		{
			editBoxMoveDown->SetClick(false);

			editBoxMoveDown->SetInputColor({ 255, 255, 0, 255 });
			editBoxMoveDown->SetInput("Press key");

			selectKey = true;
			selectEditBox = 3;
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
	resManager->GetSharedFontResource(fontSharedBig)->DrawText("CONTROLS", 500.0f, 200.0f);

	// Button
	buttonSave->Draw();
	buttonBack->Draw();

	// EditBox
	editBoxMoveLeft->Draw();
	editBoxMoveUp->Draw();
	editBoxMoveRight->Draw();
	editBoxMoveDown->Draw();

	// Show the result in the window
	GPU_Flip(screen);
	
	return ToState::Run;
}
