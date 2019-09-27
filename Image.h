#pragma once

// SDL
//#include "SDL.h"
#include "SDL_gpu.h"

// Giving alias for data types
using file = std::string;

class Image
{
public:
	Image(GPU_Target* screen);
	~Image();

	bool Load(file filePath);
	void Free();

	void DrawImage(float x, float y);

	GPU_Image* GetGpuImage();

private:
	// Members
	GPU_Target* screen;
	GPU_Image* img;
	float x;
	float y;
};