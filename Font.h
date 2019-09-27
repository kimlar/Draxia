#pragma once

// C++
#include <iostream> // Reading file
#include <fstream> // Reading file
#include <string> // Reading file
#include <vector> // Reading file

// SDL
//#include "SDL.h"
#include "SDL_gpu.h"

// Utils
#include "Utils/Debug.h"
#include "Utils/StringHelper.h"

// Giving alias for data types
using file = std::string;
using text = std::string;
using byte = unsigned char;

class Font
{
public:
	Font(GPU_Target* screen);
	~Font();

	bool Load(file filePath);
	void Free();

	void DrawText(text string, float x, float y);
		
	void SetColor(byte r, byte g, byte b, byte a = 255);
	void SetScale(float scale);

	//void SetRotation(float rotation);
	//void SetTranslate(float x, float y);
	//void SetOrigin(float x, float y);

private:

	// Structs
	struct FontData
	{
		GPU_Rect texture;
		short X; //offset of character (x,y) relative to top-left
		short Y;
		unsigned short AdvX; //x-advance after character
	};
	struct FontKerning
	{
		unsigned char first;
		unsigned char second;
		short distance;
	};

	// Methods
	void DrawChar(byte ch);
	void DrawCharScale(byte ch);

	// Members
	GPU_Target* screen;
	GPU_Image* imgFont;
	float x;
	float y;
	float scale;

	FontData stFontData[128];
	FontKerning stFontKerning[256];
	unsigned short stFontKerningNum;
};
