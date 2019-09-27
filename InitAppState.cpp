#include "InitAppState.h"



InitAppState::InitAppState()
{
	stateName = "InitApp";
}

void InitAppState::Enter()
{

}

void InitAppState::Exit()
{
	stateManager = nullptr;
	resManager = nullptr;
	settings = nullptr;
	screen = nullptr;
}

GotoState InitAppState::Update()
{
	stateManager = this->GetStateManager();

	// Read the settings file and keep it in state manager
	stateManager->ReadSettings();
	settings = stateManager->GetSettings();
	
	// Tell us whenever something bad happens
	#ifdef _DEBUG
		GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);
	#else
		GPU_SetDebugLevel(GPU_DEBUG_LEVEL_0);
	#endif

	// Get a 1920x1080 window to render to
	screen = GPU_Init(settings->GetWindowWidth(), settings->GetWindowHeight(), GPU_DEFAULT_INIT_FLAGS);

	// Did initialization fail?
	if (screen == NULL)
		return 1;
	
	// Set VSync On/Off
	SDL_GL_SetSwapInterval(settings->GetVSync()); // 0:VSync off, 1:VSync on (default)

	// Go fullscreen
	if (settings->GetFullscreen())
		GPU_SetFullscreen(true, false);

	// Get windowID. A direct ID to our window.
	SDL_Window* window = SDL_GetWindowFromID(screen->context->windowID);
	SDL_SetWindowTitle(window, "Draxia");

	// Clear the screen
	//GPU_Clear(screen);

	// Show the result in the window
	//GPU_Flip(screen);

	// Give the state manager the GPU_Target
	stateManager->SetGpuTarget(screen);

	// Give the state manager the resource manager
	stateManager->SetResourceManager(new ResourceManager(screen));
	resManager = stateManager->GetResourceManager();

	//
	// Load resources
	//

	// Font
	fontSharedBig = resManager->AddSharedFontResource("Data\\Fonts\\OpenSans-Regular-64.fnt");

	return ToState::Run;
}
