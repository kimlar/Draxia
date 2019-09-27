
//
// TODO:
//
// 1. Enum the TitleMenu
// 2. Make ESC in GamePlay show an in game menu. "Return to game", "Save game", "Load game", "Options", "Exit to menu"
//    Also: Are you sure you want to quit this game?
// 3. Make InGameMenuState. Use shared resources -> Do not load the font.
// 8. Make TriangleBatch class.
// 9. Make GameWinTrigger.
// 10. Make GameLoseTrigger.
// 11. Make (player) InZoneTrigger.
// 12. Make collision checking against stuff. Do not move if collide.
// 13. Make GameWorld class.
// 14. Make Inventory class.
// 15. Make Entity/GameObject class.
// 16. Make House object.
// 17. Make Save/Load game.
// 18. Make Player class. Life, Speed, Inventory, Weapon, Armor, Boots ...
// 19. Make ResSound class.
// 20. Make Logger class.
// 21. Make HUD class.
// 22. Make GameMessage class.
// 23. Make GameScript class.
// 24. Make Animation class.
// 25. Make DayNight cycle class.
// 26. Make Environment class. Rain, Clouds etc..
// 27. Make Projectile class.
// 28. Make Effect class. Fire/Smoke/Water/Dust/Sparkle/Ice/Snow ...
// 29. Make MouseCursor class.
// 30. Make ErrorManager and Error class.
// 31. Use fontBig as a sing shared font (for resManager)
// 32. Create Label class (GUI)
//		1. Then remove text from other GUI-controls -> replace it with Label instead.
// 33. Make default font: fontDefault => Open Sans
// 34. TitleMenu to have:
//		1. Background image
//		2. Sounds (UI)
//		3. Music
//		4. Animation (SFX)
// 35. Create MouseCursor class. Replace the OS mouse cursor.
// 36. TODO: In fullscreen make the game enter fullscreen/windows by ALT+ENTER.
// 37. Change the display modes to have: Window, Fullscreen, Borderless Window
// 38. Options->Video: Video Resolution: Get all availible video resolutions, then put it in the list.
// 39. Options->Video: Choose which monitor use on fullscreen.
// 40. Create an user friendly keyboard input names (key bindings). IE: SDLK_w -> W (display only)
// 41. Create a game icon.
// 42. Show the game icon in the titlebar.
// 43. Make the game icon on the EXE-file. [EXE Resource]
// 44. Add copy right info on the EXE-file. [EXE Resource]




// C++


// SDL
#include "SDL.h"
#include "SDL_gpu.h"

// Utils
//#include "Utils/Debug.h"
//#include "Utils/FastGPU.h" // Make another EXE just for this one. Can not switch this programmatic to use fastest GPU.


// Project
#include "Settings.h"
#include "ResourceManager.h"
#include "StateManager.h"
#include "InitAppState.h"
#include "TitleMenuState.h"
#include "GameLoadState.h"
#include "GamePlayState.h"
#include "OptionsState.h"
#include "OptionsVideoState.h"
#include "OptionsSoundState.h"
#include "OptionsGameState.h"
#include "OptionsControlsState.h"


int main(int argc, char** argv)
{
	// Creating the game state manager
	StateManager* stateManager = new StateManager();
	stateManager->AddState(new InitAppState());
	stateManager->Update();

	// Title menu
	stateManager->RemoveState();
	stateManager->AddState(new TitleMenuState());

	// Game loop
	bool run = true;
	while (run)
	{
		switch (stateManager->Update())
		{
		case ToState::Run:
			break;
		case ToState::GamePlay:
			stateManager->ReplaceState(new GamePlayState());
			break;
		case ToState::GameLoad:
			stateManager->AddState(new GameLoadState());
			break;
		case ToState::TitleMenu:
			stateManager->RemoveState();
			break;
		case ToState::Options:
			if (stateManager->GetState()->GetStateName() == "TitleMenu")
				stateManager->AddState(new OptionsState());
			else
				stateManager->ReplaceState(new OptionsState());
			break;
		case ToState::OptionsVideo:
			stateManager->ReplaceState(new OptionsVideoState());
			break;
		case ToState::OptionsSound:
			stateManager->ReplaceState(new OptionsSoundState());
			break;
		case ToState::OptionsGame:
			stateManager->ReplaceState(new OptionsGameState());
			break;
		case ToState::OptionsControls:
			stateManager->ReplaceState(new OptionsControlsState());
			break;
		case ToState::Quit:
			stateManager->Free();
			run = false;
			break;
		}
	}

	// Shutdown SDL2 and SDL_gpu
	GPU_Quit();

	// Clean up
	if (stateManager)
		delete stateManager;
	stateManager = nullptr;

	// Exit to OS
	return 0;
}
