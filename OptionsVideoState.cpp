#include "OptionsVideoState.h"


OptionsVideoState::OptionsVideoState()
{
	stateName = "OptionsVideo";
}

void OptionsVideoState::Enter()
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

	// CheckBox
	checkBoxFullscreen = new CheckBox(stateManager, fontSharedBig, "Fullscreen", 500.0f, 400.0f, true);
	checkBoxFullscreen->SetOn(settings->GetFullscreen());
	checkBoxVSync = new CheckBox(stateManager, fontSharedBig, "Vertical Sync", 500.0f, 500.0f, true);
	checkBoxVSync->SetOn(settings->GetVSync());
	checkBoxFastGPU = new CheckBox(stateManager, fontSharedBig, "Fast GPU", 500.0f, 600.0f, true);
	checkBoxFastGPU->SetOn(settings->GetFastGpu());

	// DropList
	dropListResolution = new DropList(stateManager, fontSharedBig, "Resolution", 500.0f, 300.0f, true);

	//
	// Inputs
	//
	keyEsc = false;

	// Menu
	needRestartApplication = false;

	// Fill data items into drop list
	dropListResolution->AddItem("1024x768");
	dropListResolution->AddItem("1280x720");
	dropListResolution->AddItem("1280x800");
	dropListResolution->AddItem("1280x1024");
	dropListResolution->AddItem("1360x768");
	dropListResolution->AddItem("1366x768");
	dropListResolution->AddItem("1440x900");
	dropListResolution->AddItem("1600x900");
	dropListResolution->AddItem("1680x1050");
	dropListResolution->AddItem("1920x1080");
	dropListResolution->AddItem("1920x1200");
	dropListResolution->SetItemSelectedByText(std::to_string(settings->GetWindowWidth()) + "x" + std::to_string(settings->GetWindowHeight()));
}

void OptionsVideoState::Exit()
{
	resManager->FreeResources();
	fontSharedBig = 0;

	if (checkBoxFullscreen)
		delete checkBoxFullscreen;
	checkBoxFullscreen = nullptr;

	if (checkBoxVSync)
		delete checkBoxVSync;
	checkBoxVSync = nullptr;

	if (checkBoxFastGPU)
		delete checkBoxFastGPU;
	checkBoxFastGPU = nullptr;

	if (buttonSave)
		delete buttonSave;
	buttonSave = nullptr;

	if (buttonBack)
		delete buttonBack;
	buttonBack = nullptr;

	if (dropListResolution)
		delete dropListResolution;
	dropListResolution = nullptr;

	resManager = nullptr;
	stateManager = nullptr;
	settings = nullptr;
	screen = nullptr;
}

GotoState OptionsVideoState::Update()
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
				if (!dropListResolution->EscIsPressed())
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

		// Check "Resolution"
		dropListResolution->Event(e);
		if (dropListResolution->GetClick())
		{
			dropListResolution->SetClick(false);

			// Obtain wanted resolution from the drop list.
			std::string tItem = dropListResolution->GetItemSelected();
			settings->SetWindowWidth(std::stoi(tItem.substr(0, tItem.find_first_of('x'))));
			settings->SetWindowHeight(std::stoi(tItem.substr(tItem.find_first_of('x')+1)));
		}
		// Check "Fullscreen"
		checkBoxFullscreen->Event(e);
		if (checkBoxFullscreen->GetClick())
		{
			checkBoxFullscreen->SetClick(false);

			settings->SetFullscreen(!settings->GetFullscreen());
		}
		// Check "VSync"
		checkBoxVSync->Event(e);
		if (checkBoxVSync->GetClick())
		{
			checkBoxVSync->SetClick(false);

			settings->SetVSync(!settings->GetVSync());
		}
		// Check "FastGPU"
		checkBoxFastGPU->Event(e);
		if (checkBoxFastGPU->GetClick())
		{
			checkBoxFastGPU->SetClick(false);

			settings->SetFastGpu(!settings->GetFastGpu());
		}
		// Check "Save"
		buttonSave->Event(e);
		if (buttonSave->GetClick())
		{
			buttonSave->SetClick(false);

			// Write to file
			settings->Save();

			needRestartApplication = true;
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
	resManager->GetSharedFontResource(fontSharedBig)->DrawText("VIDEO OPTIONS", 500.0f, 200.0f);

	//
	if (needRestartApplication)
	{
		resManager->GetSharedFontResource(fontSharedBig)->SetColor(160, 160, 160, 255);
		resManager->GetSharedFontResource(fontSharedBig)->DrawText("Need to restart to change resolution", 100.0f, 100.0f);
	}

	// Button
	buttonSave->Draw();
	buttonBack->Draw();

	// CheckBox
	checkBoxFullscreen->Draw();
	checkBoxVSync->Draw();
	checkBoxFastGPU->Draw();

	// DropList
	dropListResolution->Draw();

	// Show the result in the window
	GPU_Flip(screen);
	
	return ToState::Run;
}
