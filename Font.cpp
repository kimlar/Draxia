#include "Font.h"

Font::Font(GPU_Target* screen)
{
	this->screen = screen;
	x = 0.0f;
	y = 0.0f;
	scale = 1.0f;
}

Font::~Font()
{
	if(imgFont)
		Free();

	screen = nullptr;
	imgFont = nullptr;
}

bool Font::Load(file fontFilePath)
{
	// Load font image
	file fontFilePng = fontFilePath.substr(0, fontFilePath.size() - 3) + "png";
	imgFont = GPU_LoadImage(fontFilePng.c_str());
	if (imgFont == NULL)
	{
		DEBUG_PRINT("LoadFont(): Unable to open file: " << fontFilePng);
		return false;
	}

	// Load font data - Read the entire file
	std::vector<std::string> fontData;
	std::string lineData;
	std::ifstream fontFile(fontFilePath);
	if (fontFile.is_open())
	{
		while (getline(fontFile, lineData))
		{
			fontData.push_back(lineData);
		}
		fontFile.close();
	}
	else
	{
		DEBUG_PRINT("LoadFont(): Unable to open file: " << fontFilePath);
		return false;
	}

	// Parse font data
	enum FileSection { NA = 0, CHARACTERS, KERNINGS };
	int fileSection = FileSection::NA;
	for (int i = 0; i < fontData.size(); i++)
	{
		// Remove comments
		fontData[i] = fontData[i].substr(0, fontData[i].find('#'));

		// Find file sections
		if (ToUpper(fontData[i].substr(0, fontData[i].length())) == "CHARACTERS:")
		{
			fileSection = FileSection::CHARACTERS;
			continue;
		}
		else if (ToUpper(fontData[i].substr(0, fontData[i].size())) == "KERNINGS:")
		{
			fileSection = FileSection::KERNINGS;
			stFontKerningNum = -1;
			continue;
		}

		if (fileSection == FileSection::CHARACTERS)
		{
			std::vector<std::string> splitLine;
			int curSplitPos = 0;
			for (int j = 0; j < fontData[i].length(); j++)
			{
				if (fontData[i][j] == ',')
				{
					splitLine.push_back(fontData[i].substr(curSplitPos, j - curSplitPos));
					curSplitPos = ++j;
				}
			}
			if (curSplitPos != 0)
			{
				splitLine.push_back(fontData[i].substr(curSplitPos));
				FontData tFD;
				int tFD_id = std::stoi(splitLine[0]);
				tFD.texture.x = (float)std::stoi(splitLine[1]);
				tFD.texture.y = (float)std::stoi(splitLine[2]);
				tFD.texture.w = (float)std::stoi(splitLine[3]);
				tFD.texture.h = (float)std::stoi(splitLine[4]);
				tFD.X = std::stoi(splitLine[5]);
				tFD.Y = std::stoi(splitLine[6]);
				tFD.AdvX = std::stoi(splitLine[7]);
				stFontData[tFD_id] = tFD;
				splitLine.clear();
			}
		}
		else if (fileSection == FileSection::KERNINGS)
		{
			std::vector<std::string> splitLine;
			int curSplitPos = 0;
			for (int j = 0; j < fontData[i].length(); j++)
			{
				if (fontData[i][j] == ',')
				{
					splitLine.push_back(fontData[i].substr(curSplitPos, j - curSplitPos));
					curSplitPos = ++j;
				}
			}
			if (curSplitPos != 0)
			{
				splitLine.push_back(fontData[i].substr(curSplitPos));
				FontKerning tFK;
				tFK.first = std::stoi(splitLine[0]);
				tFK.second = std::stoi(splitLine[1]);
				tFK.distance = std::stoi(splitLine[2]);
				stFontKerningNum++;
				stFontKerning[stFontKerningNum] = tFK;
				splitLine.clear();
			}
		}
	}
	fontData.clear();

	return true; // All OK
}
void Font::Free()
{
	if (imgFont == NULL)
		return;

	GPU_FreeImage(imgFont);
	imgFont = nullptr;
}

void Font::DrawText(text string, float x, float y)
{
	unsigned char first = ' ';
	short kerning = 0;

	for (int i = 0; i < string.size(); i++)
	{
		// Kerning
		kerning = 0;
		for (int j = 0; j < stFontKerningNum; j++)
		{
			if (first == stFontKerning[j].first && string[i] == stFontKerning[j].second)
			{
				kerning = stFontKerning[j].distance;
				break;
			}
		}

		// Draw letter
		if (scale == 1.0f)
		{
			this->x = x + kerning;
			this->y = y;
			DrawChar(string[i]);
			x += stFontData[string[i]].AdvX;
		}
		else
		{
			this->x = (x + kerning) * scale;
			this->y = y * scale;
			DrawCharScale(string[i]);
			x += stFontData[string[i]].AdvX * scale;
		}

		// Keep kerning
		first = string[i];
	}
}

void Font::SetColor(byte r, byte g, byte b, byte a)
{
	GPU_SetColor(imgFont, { r, g, b, a });
}

void Font::SetScale(float scale)
{
	this->scale = scale;
}

void Font::DrawChar(byte ch)
{
	GPU_Blit(imgFont, &stFontData[ch].texture, screen, x + stFontData[ch].X, y - stFontData[ch].Y);
}

void Font::DrawCharScale(byte ch)
{
	GPU_BlitScale(imgFont, &stFontData[ch].texture, screen, x + stFontData[ch].X, y - stFontData[ch].Y, scale, scale);
}
