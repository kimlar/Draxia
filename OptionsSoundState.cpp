#include "OptionsSoundState.h"

OptionsSoundState::OptionsSoundState()
{
	stateName = "OptionsSound";
}

void OptionsSoundState::Enter()
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
	buttonSave = new Button(stateManager, fontSharedBig, "Save", 500.0f, 700.0f, true);
	buttonBack = new Button(stateManager, fontSharedBig, "Back", 500.0f, 800.0f, true);

	// Slider
	sliderMasterVolume = new Slider(stateManager, fontSharedBig, "Master Volume", 500.0f, 300.0f, true);
	sliderMasterVolume->SetValue(settings->GetMasterVolume());
	sliderVoiceVolume = new Slider(stateManager, fontSharedBig, "Voice Volume", 500.0f, 400.0f, true);
	sliderVoiceVolume->SetValue(settings->GetVoiceVolume());
	sliderSfxVolume = new Slider(stateManager, fontSharedBig, "SFX Volume", 500.0f, 500.0f, true);
	sliderSfxVolume->SetValue(settings->GetSoundEffectVolume());
	sliderMusicVolume = new Slider(stateManager, fontSharedBig, "Music Volume", 500.0f, 600.0f, true);
	sliderMusicVolume->SetValue(settings->GetMusicVolume());

	//
	// Inputs
	//
	keyEsc = false;
}

void OptionsSoundState::Exit()
{
	resManager->FreeResources();
	fontSharedBig = 0;

	if (sliderMasterVolume)
		delete sliderMasterVolume;
	sliderMasterVolume = nullptr;

	if (sliderVoiceVolume)
		delete sliderVoiceVolume;
	sliderVoiceVolume = nullptr;

	if (sliderSfxVolume)
		delete sliderSfxVolume;
	sliderSfxVolume = nullptr;

	if (sliderMusicVolume)
		delete sliderMusicVolume;
	sliderMusicVolume = nullptr;

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

GotoState OptionsSoundState::Update()
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

		// Check "Master Volume"
		sliderMasterVolume->Event(e);
		if (sliderMasterVolume->GetClick())
		{
			sliderMasterVolume->SetClick(false);
			settings->SetMasterVolume(sliderMasterVolume->GetValue());
		}
		// Check "Voice Volume"
		sliderVoiceVolume->Event(e);
		if (sliderVoiceVolume->GetClick())
		{
			sliderVoiceVolume->SetClick(false);
			settings->SetVoiceVolume(sliderVoiceVolume->GetValue());
		}
		// Check "SFX Volume"
		sliderSfxVolume->Event(e);
		if (sliderSfxVolume->GetClick())
		{
			sliderSfxVolume->SetClick(false);
			settings->SetSoundEffectVolume(sliderSfxVolume->GetValue());
		}
		// Check "Music Volume"
		sliderMusicVolume->Event(e);
		if (sliderMusicVolume->GetClick())
		{
			sliderMusicVolume->SetClick(false);
			settings->SetMusicVolume(sliderMusicVolume->GetValue());
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
	resManager->GetSharedFontResource(fontSharedBig)->DrawText("SOUND OPTIONS", 500.0f, 200.0f);
	
	// Button
	buttonSave->Draw();
	buttonBack->Draw();

	// Slider
	sliderMasterVolume->Draw();
	sliderVoiceVolume->Draw();
	sliderSfxVolume->Draw();
	sliderMusicVolume->Draw();

	// Show the result in the window
	GPU_Flip(screen);
	
	return ToState::Run;
}
