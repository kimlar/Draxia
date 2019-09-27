#include "GameLoadState.h"


GameLoadState::GameLoadState()
{
	stateName = "GameLoad";
}

GameLoadState::~GameLoadState()
{
	resManager = nullptr;
}

void GameLoadState::Enter()
{
	stateManager = this->GetStateManager();
	resManager = stateManager->GetResourceManager();
}

void GameLoadState::Exit()
{
	resManager = nullptr;
	stateManager = nullptr;
}

GotoState GameLoadState::Update()
{
	// TODO: Should be async to get smooth moving loading screen with UI response.
	
	//
	// Load resources
	//

	// Font
	fontSharedBig = resManager->GetSharedFontResourceIdByName("Data\\Fonts\\OpenSans-Regular-64.fnt");

	// Image
	std::vector<std::string> vLoadImage;
	vLoadImage.push_back("Data\\__General__\\spr_body_0.png");
	vLoadImage.push_back("Data\\__General__\\bg_grass.png");
	vLoadImage.push_back("Data\\TinyHouse\\spr_tinyhouse_floor_0.png");
	vLoadImage.push_back("Data\\TinyHouse\\tinyhouseOutWest.png");

	// Load images onto the GPU
	for(int i = 0; i < vLoadImage.size(); i++)
		resManager->AddGpuImageResource(vLoadImage[i]);
	vLoadImage.clear();


	return ToState::GamePlay;
}
