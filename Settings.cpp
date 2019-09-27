#include "Settings.h"

// C++
#include <iostream>		// for writing file
#include <fstream>      // std::ifstream

// Utils
#include "Utils/Debug.h"
#include "Utils/StringHelper.h"

// Project
#include "Controls.h"

Settings::Settings()
{
	// Video Options
	windowWidth = 1024;
	windowHeight = 768;
	fullscreen = false;
	vsync = 1; // 0:VSync off, 1:VSync on (default)
	fastGPU = false;

	// Sound Options
	masterVolume = 100;
	voiceVolume = 100;
	soundEffectsVolume = 100;
	musicVolume = 100;

	// Game Options
	showFPS = false;

	// Controls
	moveLeft = GetValueByKey("SDLK_LEFT");
	moveUp = GetValueByKey("SDLK_UP");
	moveRight = GetValueByKey("SDLK_RIGHT");
	moveDown = GetValueByKey("SDLK_RIGHT");
	//moveLeft = Controls::LEFT;
	//moveUp = Controls::UP;
	//moveRight = Controls::RIGHT;
	//moveDown = Controls::DOWN;
}

Settings::~Settings()
{

}

bool Settings::Load()
{
	// Read file: Settings.txt
	std::string line;
	std::ifstream myfile("Settings.txt");

	std::string keyword;
	std::string value;
	std::string valueCased;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			// Remove comments
			line = line.substr(0, line.find('#'));

			// Remove empty space at beginning
			if (line != "")
				line = line.substr(line.find_first_not_of(' '));

			// Get the keyword and value
			std::size_t found = line.find('=');
			if (found != std::string::npos)
			{
				keyword = line.substr(0, found);
				value = line.substr(found + 1);

				// Trim it
				keyword = keyword.substr(0, keyword.find_first_of(' '));
				value = value.substr(value.find_first_not_of(' '));

				// Save original
				valueCased = value;

				// Upper case it
				keyword = ToUpper(keyword);
				value = ToUpper(value);
			}

			// Handle each keyword with value
			if (keyword == "VIDEORESOLUTION")
			{
				std::size_t vr_found = value.find('X');
				if (vr_found != std::string::npos)
				{
					windowWidth = std::stoi(value.substr(0, vr_found));
					windowHeight = std::stoi(value.substr(vr_found + 1));
				}
			}
			else if (keyword == "FULLSCREEN")
			{
				fullscreen = (value == "ON" ? true : false);
			}
			else if (keyword == "VSYNC")
			{
				vsync = (value == "ON" ? true : false);
			}
			else if (keyword == "FASTGPU")
			{
				fastGPU = (value == "ON" ? true : false);
			}
			else if (keyword == "MASTERVOLUME")
			{
				masterVolume = std::stoi(value);
			}
			else if (keyword == "VOICEVOLUME")
			{
				voiceVolume = std::stoi(value);
			}
			else if (keyword == "SOUNDEFFECTSVOLUME")
			{
				soundEffectsVolume = std::stoi(value);
			}
			else if (keyword == "MUSICVOLUME")
			{
				musicVolume = std::stoi(value);
			}
			else if (keyword == "SHOWFPS")
			{
				showFPS = (value == "ON" ? true : false);
			}
			else if (keyword == "MOVELEFT")
			{
				moveLeft = GetValueByKey(valueCased);
			}
			else if (keyword == "MOVEUP")
			{
				moveUp = GetValueByKey(valueCased);
			}
			else if (keyword == "MOVERIGHT")
			{
				moveRight = GetValueByKey(valueCased);
			}
			else if (keyword == "MOVEDOWN")
			{
				moveDown = GetValueByKey(valueCased);
			}
		}
		myfile.close();
	}
	else
	{
		DEBUG_PRINT("Unable to open file: Settings.txt");
		return false;
	}

	return true;
}

void Settings::Save()
{
	std::ofstream myfile;
	myfile.open("Settings.txt", std::ios::out | std::ios::trunc);
	myfile << "# Video Options" << "\n";
	myfile << "VideoResolution=" << GetWindowWidth() << "x" << GetWindowHeight() << "\n";
	myfile << "Fullscreen=" << (GetFullscreen() ? "on" : "off") << "\n";
	myfile << "VSync=" << (GetVSync() ? "on" : "off") << "\n";
	myfile << "FastGPU=" << (GetFastGpu() ? "on" : "off") << "\n";
	myfile << "\n";
	myfile << "# Sound Options" << "\n";
	myfile << "MasterVolume=" << GetMasterVolume() << "\n";
	myfile << "VoiceVolume=" << GetVoiceVolume() << "\n";
	myfile << "SoundEffectsVolume=" << GetSoundEffectVolume() << "\n";
	myfile << "MusicVolume=" << GetMusicVolume() << "\n";
	myfile << "\n";
	myfile << "# Game Options" << "\n";
	myfile << "ShowFPS=" << (GetShowFps() ? "on" : "off") << "\n";
	myfile << "\n";
	myfile << "# Controls" << "\n";
	myfile << "MoveLeft=" << GetKeyByValue(GetMoveLeft()) << "\n";
	myfile << "MoveUp=" << GetKeyByValue(GetMoveUp()) << "\n";
	myfile << "MoveRight=" << GetKeyByValue(GetMoveRight()) << "\n";
	myfile << "MoveDown=" << GetKeyByValue(GetMoveDown()) << "\n";

	/*
	# Video Options
	VideoResolution=1600x900
	Fullscreen=off
	VSync=off
	FastGPU=off

	# Sound Options
	MasterVolume=100
	VoiceVolume=100
	SoundEffectsVolume=100
	MusicVolume=100

	# Game Options
	ShowFPS=on

	# Controls
	MoveLeft=LEFT
	MoveUp=UP
	MoveRight=RIGHT
	MoveDown=DOWN
	*/
	myfile.close();
}

int Settings::GetWindowWidth()
{
	return windowWidth;
}

void Settings::SetWindowWidth(int width)
{
	this->windowWidth = width;
}

int Settings::GetWindowHeight()
{
	return windowHeight;
}

void Settings::SetWindowHeight(int height)
{
	this->windowHeight = height;
}

bool Settings::GetFullscreen()
{
	return fullscreen;
}

void Settings::SetFullscreen(bool fullscreen)
{
	this->fullscreen = fullscreen;
}

bool Settings::GetVSync()
{
	return vsync;
}

void Settings::SetVSync(bool vsync)
{
	this->vsync = vsync;
}

bool Settings::GetFastGpu()
{
	return fastGPU;
}

void Settings::SetFastGpu(bool fastgpu)
{
	this->fastGPU = fastgpu;
}

int Settings::GetMasterVolume()
{
	return masterVolume;
}

void Settings::SetMasterVolume(int volume)
{
	this->masterVolume = volume;
}

int Settings::GetVoiceVolume()
{
	return voiceVolume;
}

void Settings::SetVoiceVolume(int volume)
{
	this->voiceVolume = volume;
}

int Settings::GetSoundEffectVolume()
{
	return soundEffectsVolume;
}

void Settings::SetSoundEffectVolume(int volume)
{
	this->soundEffectsVolume = volume;
}

int Settings::GetMusicVolume()
{
	return musicVolume;
}

void Settings::SetMusicVolume(int volume)
{
	this->musicVolume = volume;
}

bool Settings::GetShowFps()
{
	return showFPS;
}

void Settings::SetShowFps(bool showfps)
{
	this->showFPS = showfps;
}

int Settings::GetMoveLeft()
{
	return moveLeft;
}

void Settings::SetMoveLeft(int keyLeft)
{
	this->moveLeft = keyLeft;
}

int Settings::GetMoveUp()
{
	return moveUp;
}

void Settings::SetMoveUp(int keyUp)
{
	this->moveUp = keyUp;
}

int Settings::GetMoveRight()
{
	return moveRight;
}

void Settings::SetMoveRight(int keyRight)
{
	this->moveRight = keyRight;
}

int Settings::GetMoveDown()
{
	return moveDown;
}

void Settings::SetMoveDown(int keyDown)
{
	this->moveDown = keyDown;
}
