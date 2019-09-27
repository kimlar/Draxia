#include "EditBox.h"

EditBox::EditBox(StateManager* stateManager, ResID fontResID, std::string label, float x, float y, bool sharedFont) : stateManager(stateManager), fontResID(fontResID), label(label), x(x), y(y), sharedFont(sharedFont)
{
	resManager = stateManager->GetResourceManager();
	screen = stateManager->GetGpuTarget();

	width = x + 300.0f;
	height = y + 60.0f;

	ex = width + 40.0f;
	ey = y;
	ew = ex + 330.0f;
	eh = height;

	tx = width + 50.0f + 20.0f;
	ty = y + 30.0f;

	edgeLightColor = { 127, 127, 127, 255 };
	edgeDarkColor = { 27, 27, 27, 255 };
	fillColor = { 55, 55, 55, 255 };
	//hoverColor = { 127, 127, 127, 255 };
	hoverColor = { 63, 63, 63, 255 };
	textColor = { 255, 255, 255, 255 };
	inputColor = { 255, 255, 255, 255 };

	click = false;

	input = "";
}

EditBox::~EditBox()
{
	Free();
}

void EditBox::Free()
{
	resManager = nullptr;
	stateManager = nullptr;
	screen = nullptr;
}

void EditBox::Draw()
{
	// EditBox
	if (GetEvent() == EditBoxEventState::Hover)
		GPU_RectangleFilled(screen, ex, ey, ew, eh, hoverColor);
	GPU_Rectangle(screen, ex, ey, ew, eh, edgeLightColor);
	//GPU_Line(screen, x, y, width, y, edgeLightColor);
	//GPU_Line(screen, x, y, x, height, edgeLightColor);
	//GPU_Line(screen, x, height, width, height, edgeDarkColor);
	//GPU_Line(screen, width, y, width, height, edgeDarkColor);
	//GPU_Rectangle(screen, x, y, width, height, { 255,0,0,255 });
	//GPU_Rectangle(screen, x+1, y+1, width-1, height-1, { 0,0,255,255 });

	// Input
	if (sharedFont)
	{
		resManager->GetSharedFontResource(fontResID)->SetColor(inputColor.r, inputColor.g, inputColor.b, inputColor.a);
		resManager->GetSharedFontResource(fontResID)->DrawText(input, tx, ty);
	}
	else
	{
		resManager->GetFontResource(fontResID)->SetColor(inputColor.r, inputColor.g, inputColor.b, inputColor.a);
		resManager->GetFontResource(fontResID)->DrawText(input, tx, ty);
	}

	// Label
	if (sharedFont)
	{
		resManager->GetSharedFontResource(fontResID)->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
		resManager->GetSharedFontResource(fontResID)->DrawText(label, x + 25.0f, y + 30.0f);
	}
	else
	{
		resManager->GetFontResource(fontResID)->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
		resManager->GetFontResource(fontResID)->DrawText(label, x + 25.0f, y + 30.0f);
	}
}

void EditBox::Event(SDL_Event &e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if ((e.motion.x >= ex) && (e.motion.x < ew) && (e.motion.y >= ey) && (e.motion.y < eh))
		{
			SetEvent(EditBox::EditBoxEventState::Down);
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		SetEvent(EditBox::EditBoxEventState::Up);
		if ((e.motion.x >= ex) && (e.motion.x < ew) && (e.motion.y >= ey) && (e.motion.y < eh))
		{
			SetClick(true);
		}
	}
	else if ((e.motion.x >= ex) && (e.motion.x < ew) && (e.motion.y >= ey) && (e.motion.y < eh))
	{
		if (GetEvent() != EditBoxEventState::Down)
		{
			SetEvent(EditBox::EditBoxEventState::Hover);
		}
	}
	else
	{
		SetEvent(EditBox::EditBoxEventState::Up);
	}
}

void EditBox::SetEvent(EditBoxEventState ebeState)
{
	this->editBoxEventState = ebeState;
}

EditBox::EditBoxEventState EditBox::GetEvent()
{
	return editBoxEventState;
}

void EditBox::SetClick(bool click)
{
	this->click = click;
}

bool EditBox::GetClick()
{
	return click;
}

void EditBox::SetInput(std::string input)
{
	this->input = input;
}

std::string EditBox::GetInput()
{
	return input;
}

void EditBox::SetInputColor(SDL_Color color)
{
	this->inputColor = color;
}
