#include "Button.h"

Button::Button(StateManager* stateManager, ResID fontResID, std::string text, float x, float y, bool sharedFont) : stateManager(stateManager), fontResID(fontResID), text(text), x(x), y(y), sharedFont(sharedFont)
{
	resManager = stateManager->GetResourceManager();
	screen = stateManager->GetGpuTarget();

	//width = x + 9.0f * text.length() + 100.0f;
	width = x + 300.0f;
	height = y + 60.0f;

	edgeLightColor = { 127, 127, 127, 255 };
	edgeDarkColor = { 27, 27, 27, 255 };
	fillColor = { 55, 55, 55, 255 };
	hoverColor = { 127, 127, 127, 255 };
	textColor = { 255, 255, 255, 255 };

	click = false;
}

Button::~Button()
{
	Free();
}

void Button::Free()
{
	resManager = nullptr;
	stateManager = nullptr;
	screen = nullptr;
}

void Button::Draw()
{
	if (buttonEventState == ButtonEventState::Down)
	{
		xDown = 2.0f;
		yDown = 2.0f;
	}
	else
	{
		xDown = 0.0f;
		yDown = 0.0f;
	}

	// Button
	if(GetEvent() == ButtonEventState::Hover)
		GPU_RectangleFilled(screen, x + xDown, y + yDown, width + xDown, height + yDown, hoverColor);
	else
		GPU_RectangleFilled(screen, x + xDown, y + yDown, width + xDown, height + yDown, fillColor);
	GPU_Line(screen, x + xDown, y + yDown, width + xDown, y + yDown, edgeLightColor);
	GPU_Line(screen, x + xDown, y + yDown, x + xDown, height + yDown, edgeLightColor);
	GPU_Line(screen, x + xDown, height + yDown, width + xDown, height + yDown, edgeDarkColor);
	GPU_Line(screen, width + xDown, y + yDown, width + xDown, height + yDown, edgeDarkColor);
	//GPU_Rectangle(screen, x, y, width, height, { 255,0,0,255 });
	//GPU_Rectangle(screen, x+1, y+1, width-1, height-1, { 0,0,255,255 });

	// Text
	if (sharedFont)
	{
		resManager->GetSharedFontResource(fontResID)->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
		resManager->GetSharedFontResource(fontResID)->DrawText(text, x + xDown + 25.0f, y + yDown + 30.0f);
	}
	else
	{
		resManager->GetFontResource(fontResID)->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
		resManager->GetFontResource(fontResID)->DrawText(text, x + xDown + 25.0f, y + yDown + 30.0f);
	}
}

void Button::Event(SDL_Event &e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if ((e.motion.x >= x) && (e.motion.x < width) && (e.motion.y >= y) && (e.motion.y < height))
		{
			SetEvent(Button::ButtonEventState::Down);
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		SetEvent(Button::ButtonEventState::Up);
		if ((e.motion.x >= x) && (e.motion.x < width) && (e.motion.y >= y) && (e.motion.y < height))
		{
			SetClick(true);
		}
	}
	else if ((e.motion.x >= x) && (e.motion.x < width) && (e.motion.y >= y) && (e.motion.y < height))
	{
		if (GetEvent() != ButtonEventState::Down)
		{
			SetEvent(Button::ButtonEventState::Hover);
		}
	}
	else
	{
		SetEvent(Button::ButtonEventState::Up);
	}
}

void Button::SetEvent(ButtonEventState beState)
{
	this->buttonEventState = beState;
}

Button::ButtonEventState Button::GetEvent()
{
	return buttonEventState;
}

void Button::SetClick(bool click)
{
	this->click = click;
}

bool Button::GetClick()
{
	return click;
}
