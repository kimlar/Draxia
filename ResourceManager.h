#pragma once

// C++
#include <limits>       // std::numeric_limits

// SDL
//#include "SDL.h"
#include "SDL_gpu.h"

// Project
#include "Image.h"
#include "Font.h"

// Giving alias for data types
using ResID = unsigned int;
using ResName = std::string;
using file = std::string;

class ResourceManager
{
public:
	ResourceManager(GPU_Target* screen);
	~ResourceManager();

	// All (except shared)
	void FreeResources();

	// Shared
	void FreeSharedResources();

	//
	// DYNAMIC RESOURCE
	//

	// GPU Image
	ResID AddGpuImageResource(file imageFilePath);
	bool InsertGpuImageResource(ResID resID, file imageFilePath);
	void RemoveGpuImageResource(ResID resID);
	void FreeGpuImageResources();
	Image* GetGpuImageResource(ResID resID);
	ResName GetGpuImageResourceName(ResID resID);
	unsigned int GetGpuImageResourceCount();
	ResID GetGpuImageResourceIdByName(ResName resName);
	
	// Font
	ResID AddFontResource(file fontFilePath);
	bool InsertFontResource(ResID resID, file fontFilePath);
	void RemoveFontResource(ResID resID);
	void FreeFontResources();
	Font* GetFontResource(ResID resID);
	ResName GetFontResourceName(ResID resID);
	unsigned int GetFontResourceCount();
	ResID GetFontResourceIdByName(ResName resName);

	//
	// SHARED RESOURCE
	//

	// GPU Image
	ResID AddSharedGpuImageResource(file imageFilePath);
	bool InsertSharedGpuImageResource(ResID resID, file imageFilePath);
	void RemoveSharedGpuImageResource(ResID resID);
	void FreeSharedGpuImageResources();
	Image* GetSharedGpuImageResource(ResID resID);
	ResName GetSharedGpuImageResourceName(ResID resID);
	unsigned int GetSharedGpuImageResourceCount();
	ResID GetSharedGpuImageResourceIdByName(ResName resName);

	// Font
	ResID AddSharedFontResource(file fontFilePath);
	bool InsertSharedFontResource(ResID resID, file fontFilePath);
	void RemoveSharedFontResource(ResID resID);
	void FreeSharedFontResources();
	Font* GetSharedFontResource(ResID resID);
	ResName GetSharedFontResourceName(ResID resID);
	unsigned int GetSharedFontResourceCount();
	ResID GetSharedFontResourceIdByName(ResName resName);

private:

	//
	// Dynamical loaded resource (typical game resource)
	//
	std::vector<Image*> vImage;
	std::vector<ResName> vImageName;
	//
	std::vector<Font*> vFont;
	std::vector<ResName> vFontName;

	//
	// Statical loaded resource (typical shared resource
	//
	std::vector<Image*> vSharedImage;
	std::vector<ResName> vSharedImageName;
	//
	std::vector<Font*> vSharedFont;
	std::vector<ResName> vSharedFontName;


	GPU_Target* screen;
};
