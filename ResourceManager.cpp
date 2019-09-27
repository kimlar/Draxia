#include "ResourceManager.h"

#include "Utils/Debug.h"

ResourceManager::ResourceManager(GPU_Target* screen)
{
	this->screen = screen;
}

ResourceManager::~ResourceManager()
{
	FreeResources();
	screen = nullptr;
}

void ResourceManager::FreeResources()
{
	FreeGpuImageResources();
	FreeFontResources();
}

void ResourceManager::FreeSharedResources()
{
	FreeSharedGpuImageResources();
	FreeSharedFontResources();
}

//
// DYNAMIC RESOURCE
//

ResID ResourceManager::AddGpuImageResource(file imageFilePath)
{
	// Check if already loaded
	for (int i = 0; i < vImageName.size(); i++)
	{
		if (vImageName[i] == imageFilePath)
			return i;
	}

	// Load the image...
	Image* img = new Image(screen);
	img->Load(imageFilePath.c_str());
	if (img == NULL)
		return 0;	// TODO: Create a message box with error
	vImage.push_back(img);
	vImageName.push_back(imageFilePath);
	return (unsigned int)vImage.size() - 1;
}

bool ResourceManager::InsertGpuImageResource(ResID resID, file imageFilePath)
{
	// Remove the image
	RemoveGpuImageResource(resID);

	// Add the image
	Image* img = new Image(screen);
	img->Load(imageFilePath.c_str());
	if (img == NULL)
		return false;
	vImage[resID] = img;
	vImageName[resID] = imageFilePath;
	return true;
}

void ResourceManager::RemoveGpuImageResource(ResID resID)
{
	if (vImage[resID] == nullptr)
		return;

	vImage[resID]->Free();
	vImage[resID] = nullptr;
	vImageName[resID] = "";
}

void ResourceManager::FreeGpuImageResources()
{
	for (int i = 0; i < vImage.size(); i++)
	{
		if (vImage[i] == nullptr)
			continue;

		// Freeing the image
		vImage[i]->Free();
		vImage[i] = nullptr;
		vImageName[i] = "";
	}

	vImage.clear();
	vImageName.clear();
}

Image* ResourceManager::GetGpuImageResource(ResID resID)
{
	return vImage[resID];
}

ResName ResourceManager::GetGpuImageResourceName(ResID resID)
{
	return vImageName[resID];
}

unsigned int ResourceManager::GetGpuImageResourceCount()
{
	return (unsigned int)vImage.size();
}

ResID ResourceManager::GetGpuImageResourceIdByName(ResName resName)
{
	for (int i = 0; vImage.size(); i++)
	{
		if (vImageName[i] == resName)
			return i;
	}

	return 0;
}

ResID ResourceManager::AddFontResource(file fontFilePath)
{
	// Check if already loaded
	for (int i = 0; i < vFontName.size(); i++)
	{
		if (vFontName[i] == fontFilePath)
			return i;
	}

	Font* font = new Font(screen);
	if (font->Load(fontFilePath) == false)
		return 0;	// TODO: Create a message box with error

	vFont.push_back(font);
	vFontName.push_back(fontFilePath);
	return (unsigned int)vFont.size() - 1;
}

bool ResourceManager::InsertFontResource(ResID resID, file fontFilePath)
{
	// Remove the font
	RemoveFontResource(resID);

	// Add the font
	Font* font = new Font(screen);
	if (font->Load(fontFilePath) == false)
		return false;
	vFont[resID] = font;
	vFontName[resID] = fontFilePath;
	return true;
}

void ResourceManager::RemoveFontResource(ResID resID)
{
	if (vFont[resID] = nullptr)
		return;

	vFont[resID]->Free();
	vFont[resID] = nullptr;
	vFontName[resID] = "";
}

void ResourceManager::FreeFontResources()
{
	for (int i = 0; i < vFont.size(); i++)
	{
		if (vFont[i] == nullptr)
			continue;
			
		vFont[i]->Free();
		vFont[i] = nullptr;
		vFontName[i] = "";
	}

	vFont.clear();
	vFontName.clear();
}

Font* ResourceManager::GetFontResource(ResID resID)
{
	return vFont[resID];
}

ResName ResourceManager::GetFontResourceName(ResID resID)
{
	return vFontName[resID];
}

unsigned int ResourceManager::GetFontResourceCount()
{
	return (unsigned int)vFont.size();
}

ResID ResourceManager::GetFontResourceIdByName(ResName resName)
{
	for (int i = 0; vFont.size(); i++)
	{
		if (vFontName[i] == resName)
			return i;
	}

	return 0;
}





//
// SHARED RESOURCE
//

ResID ResourceManager::AddSharedGpuImageResource(file imageFilePath)
{
	// Check if already loaded
	for (int i = 0; i < vSharedImageName.size(); i++)
	{
		if (vSharedImageName[i] == imageFilePath)
			return i;
	}

	// Load the image...
	Image* img = new Image(screen);
	img->Load(imageFilePath.c_str());
	if (img == NULL)
		return 0;	// TODO: Create a message box with error
	vSharedImage.push_back(img);
	vSharedImageName.push_back(imageFilePath);
	return (unsigned int)vSharedImage.size() - 1;
}

bool ResourceManager::InsertSharedGpuImageResource(ResID resID, file imageFilePath)
{
	// Remove the image
	RemoveSharedGpuImageResource(resID);

	// Add the image
	Image* img = new Image(screen);
	img->Load(imageFilePath.c_str());
	if (img == NULL)
		return false;
	vSharedImage[resID] = img;
	vSharedImageName[resID] = imageFilePath;
	return true;
}

void ResourceManager::RemoveSharedGpuImageResource(ResID resID)
{
	if (vSharedImage[resID] == nullptr)
		return;

	vSharedImage[resID]->Free();
	vSharedImage[resID] = nullptr;
	vSharedImageName[resID] = "";
}

void ResourceManager::FreeSharedGpuImageResources()
{
	for (int i = 0; i < vSharedImage.size(); i++)
	{
		if (vSharedImage[i] == nullptr)
			continue;

		// Freeing the image
		vSharedImage[i]->Free();
		vSharedImage[i] = nullptr;
		vSharedImageName[i] = "";
	}

	vSharedImage.clear();
	vSharedImageName.clear();
}

Image* ResourceManager::GetSharedGpuImageResource(ResID resID)
{
	return vSharedImage[resID];
}

ResName ResourceManager::GetSharedGpuImageResourceName(ResID resID)
{
	return vSharedImageName[resID];
}

unsigned int ResourceManager::GetSharedGpuImageResourceCount()
{
	return (unsigned int)vSharedImage.size();
}

ResID ResourceManager::GetSharedGpuImageResourceIdByName(ResName resName)
{
	for (int i = 0; vSharedImage.size(); i++)
	{
		if (vSharedImageName[i] == resName)
			return i;
	}

	return 0;
}

ResID ResourceManager::AddSharedFontResource(file fontFilePath)
{
	// Check if already loaded
	for (int i = 0; i < vSharedFontName.size(); i++)
	{
		if (vSharedFontName[i] == fontFilePath)
			return i;
	}

	Font* font = new Font(screen);
	if (font->Load(fontFilePath) == false)
		return 0;	// TODO: Create a message box with error

	vSharedFont.push_back(font);
	vSharedFontName.push_back(fontFilePath);
	return (unsigned int)vSharedFont.size() - 1;
}

bool ResourceManager::InsertSharedFontResource(ResID resID, file fontFilePath)
{
	// Remove the font
	RemoveSharedFontResource(resID);

	// Add the font
	Font* font = new Font(screen);
	if (font->Load(fontFilePath) == false)
		return false;
	vSharedFont[resID] = font;
	vSharedFontName[resID] = fontFilePath;
	return true;
}

void ResourceManager::RemoveSharedFontResource(ResID resID)
{
	if (vSharedFont[resID] = nullptr)
		return;

	vSharedFont[resID]->Free();
	vSharedFont[resID] = nullptr;
	vSharedFontName[resID] = "";
}

void ResourceManager::FreeSharedFontResources()
{
	for (int i = 0; i < vSharedFont.size(); i++)
	{
		if (vSharedFont[i] == nullptr)
			continue;

		vSharedFont[i]->Free();
		vSharedFont[i] = nullptr;
		vSharedFontName[i] = "";
	}

	vSharedFont.clear();
	vSharedFontName.clear();
}

Font* ResourceManager::GetSharedFontResource(ResID resID)
{
	return vSharedFont[resID];
}

ResName ResourceManager::GetSharedFontResourceName(ResID resID)
{
	return vSharedFontName[resID];
}

unsigned int ResourceManager::GetSharedFontResourceCount()
{
	return (unsigned int)vSharedFont.size();
}

ResID ResourceManager::GetSharedFontResourceIdByName(ResName resName)
{
	for (int i = 0; vSharedFont.size(); i++)
	{
		if (vSharedFontName[i] == resName)
			return i;
	}

	return 0;
}
