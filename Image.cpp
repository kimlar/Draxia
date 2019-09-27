#include "Image.h"

#include "Utils/Debug.h"

Image::Image(GPU_Target* screen)
{
	this->screen = screen;
}

Image::~Image()
{
	if (img)
		Free();

	screen = nullptr;
}

bool Image::Load(file filePath)
{
	// Load the image
	img = GPU_LoadImage(filePath.c_str());
	if (img == NULL)
	{
		DEBUG_PRINT("Load(): Unable to open file: " << filePath.c_str());
		return false;
	}
	return true;
}

void Image::Free()
{
	if (img == NULL)
		return;

	GPU_FreeImage(img);
	img = nullptr;
}

void Image::DrawImage(float x, float y)
{
	GPU_Blit(img, NULL, screen, x, y);
}

GPU_Image* Image::GetGpuImage()
{
	return img;
}

