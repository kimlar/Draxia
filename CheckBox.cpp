#include "CheckBox.h"

CheckBox::CheckBox(StateManager* stateManager, ResID fontResID, std::string text, float x, float y, bool sharedFont) : stateManager(stateManager), fontResID(fontResID), text(text), x(x), y(y), sharedFont(sharedFont)
{
	resManager = stateManager->GetResourceManager();
	screen = stateManager->GetGpuTarget();

	width = x + 40.0f;
	height = y + 40.0f;

	cbx = x + 10.0f;
	cby = y + 10.0f;
	cbw = width + 10.0f;
	cbh = height + 10.0f;

	edgeLightColor = { 127, 127, 127, 255 };
	edgeDarkColor = { 27, 27, 27, 255 };
	fillColor = { 55, 55, 55, 255 };
	onColor = { 0, 224, 0, 255 };
	hoverColor = { 127, 127, 127, 255 };
	textColor = { 255, 255, 255, 255 };

	click = false;
	on = false;
}

CheckBox::~CheckBox()
{
	Free();
}

void CheckBox::Free()
{
	resManager = nullptr;
	stateManager = nullptr;
	screen = nullptr;
}

void CheckBox::Draw()
{
	// CheckBox
	if (GetEvent() == CheckBoxEventState::Hover)
		GPU_RectangleFilled(screen, cbx, cby, cbw, cbh, hoverColor);
	else
		GPU_RectangleFilled(screen, cbx, cby, cbw, cbh, fillColor);
	if (on)
		GPU_RectangleFilled(screen, cbx + 8.0f, cby + 8.0f, cbw - 8.0f, cbh - 8.0f, onColor);
	/*
	GPU_Line(screen, cbx, cby, cbw, cby, edgeLightColor);
	GPU_Line(screen, cbx, cby, cbx, cbh, edgeLightColor);
	GPU_Line(screen, cbx, cbh, cbw, cbh, edgeDarkColor);
	GPU_Line(screen, cbw, cby, cbw, cbh, edgeDarkColor);
	*/
	GPU_Rectangle(screen, cbx, cby, cbw, cbh, edgeLightColor);
	//GPU_Rectangle(screen, x, y, width, height, { 255,0,0,255 });
	//GPU_Rectangle(screen, x+1, y+1, width-1, height-1, { 0,0,255,255 });

	// Text
	if (sharedFont)
	{
		resManager->GetSharedFontResource(fontResID)->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
		resManager->GetSharedFontResource(fontResID)->DrawText(text, x + 80.0f, y + 30.0f);
	}
	else
	{
		resManager->GetFontResource(fontResID)->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
		resManager->GetFontResource(fontResID)->DrawText(text, x + 80.0f, y + 30.0f);
	}
}

void CheckBox::Event(SDL_Event &e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if ((e.motion.x >= cbx) && (e.motion.x < cbw) && (e.motion.y >= cby) && (e.motion.y < cbh))
		{
			SetEvent(CheckBox::CheckBoxEventState::Down);
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		SetEvent(CheckBox::CheckBoxEventState::Up);
		if ((e.motion.x >= cbx) && (e.motion.x < cbw) && (e.motion.y >= cby) && (e.motion.y < cbh))
		{
			SetClick(true);
			on = !on;
		}
	}
	else if ((e.motion.x >= cbx) && (e.motion.x < cbw) && (e.motion.y >= cby) && (e.motion.y < cbh))
	{
		if (GetEvent() != CheckBoxEventState::Down)
		{
			SetEvent(CheckBox::CheckBoxEventState::Hover);
		}
	}
	else
	{
		SetEvent(CheckBox::CheckBoxEventState::Up);
	}
}

void CheckBox::SetEvent(CheckBoxEventState cbeState)
{
	this->checkBoxEventState = cbeState;
}

CheckBox::CheckBoxEventState CheckBox::GetEvent()
{
	return checkBoxEventState;
}

void CheckBox::SetClick(bool click)
{
	this->click = click;
}

bool CheckBox::GetClick()
{
	return click;
}

void CheckBox::SetOn(bool on)
{
	this->on = on;
}
