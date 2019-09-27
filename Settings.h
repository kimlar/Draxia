#pragma once

class Settings
{
public:
	Settings();
	virtual ~Settings();

	bool Load();
	void Save();

	// Video Options (GET)
	int GetWindowWidth();
	void SetWindowWidth(int width);
	int GetWindowHeight();
	void SetWindowHeight(int height);
	bool GetFullscreen();
	void SetFullscreen(bool fullscreen);
	bool GetVSync();
	void SetVSync(bool vsync);
	bool GetFastGpu();
	void SetFastGpu(bool fastgpu);

	// Sound Options (GET)
	int GetMasterVolume();
	void SetMasterVolume(int volume);
	int GetVoiceVolume();
	void SetVoiceVolume(int volume);
	int GetSoundEffectVolume();
	void SetSoundEffectVolume(int volume);
	int GetMusicVolume();
	void SetMusicVolume(int volume);

	// Game Options (GET)
	bool GetShowFps();
	void SetShowFps(bool showfps);

	// Controls (GET)
	int GetMoveLeft();
	void SetMoveLeft(int keyLeft);
	int GetMoveUp();
	void SetMoveUp(int keyUp);
	int GetMoveRight();
	void SetMoveRight(int keyRight);
	int GetMoveDown();
	void SetMoveDown(int keyDown);

private:
	// Video Options
	int windowWidth; // 1024
	int windowHeight; // 768
	bool fullscreen; // false
	bool vsync; // 0:VSync off, 1:VSync on (default)
	bool fastGPU; // false

	// Sound Options
	int masterVolume; // 100
	int voiceVolume; // 100
	int soundEffectsVolume; // 100
	int musicVolume; // 100

	// Game Options
	bool showFPS; // false

	// Controls
	int moveLeft;
	int moveUp;
	int moveRight;
	int moveDown;
};
