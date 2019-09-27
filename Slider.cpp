#include "Slider.h"

Slider::Slider(StateManager* stateManager, ResID fontResID, std::string text, float x, float y, bool sharedFont) : stateManager(stateManager), fontResID(fontResID), text(text), x(x), y(y), sharedFont(sharedFont)
{
	resManager = stateManager->GetResourceManager();
	screen = stateManager->GetGpuTarget();

	width = x + 300.0f;
	height = y + 60.0f;

	rx = width + 100.0f;
	ry = y + 25.0f;
	rw = rx + 300.0f;
	rh = y + 35.0f;

	bx = rx - 10.0f;
	by = ry - 20.0f;
	bw = bx + 20.0f;
	bh = by + 50.0f;

	edgeLightColor = { 127, 127, 127, 255 };
	edgeDarkColor = { 27, 27, 27, 255 };
	fillColor = { 55, 55, 55, 255 };
	hoverColor = { 127, 127, 127, 255 };
	textColor = { 255, 255, 255, 255 };
	railColor = { 31, 31, 31, 255 };
	valueColor = { 0, 0, 255, 255 };

	click = false;
	drag = false;

	sliderValue = 0;
	//sliderMin = 0;
	//sliderMax = 100;
}

Slider::~Slider()
{
	Free();
}

void Slider::Free()
{
	resManager = nullptr;
	stateManager = nullptr;
	screen = nullptr;
}

void Slider::Draw()
{
	// Slider Rail
	GPU_RectangleFilled(screen, rx, ry, rw, rh, railColor);
	GPU_RectangleFilled(screen, rx, ry, bx + 10.0f, rh, valueColor);
	GPU_Line(screen, rx, ry, rw, ry, edgeLightColor);
	GPU_Line(screen, rx, ry, rx, rh, edgeLightColor);
	GPU_Line(screen, rx, rh, rw, rh, edgeDarkColor);
	GPU_Line(screen, rw, ry, rw, rh, edgeDarkColor);

	// Slider Button
	if (GetEvent() == SliderEventState::Hover)
		GPU_RectangleFilled(screen, bx, by, bw, bh, hoverColor);
	else
		GPU_RectangleFilled(screen, bx, by, bw, bh, fillColor);
	GPU_Line(screen, bx, by, bw, by, edgeLightColor);
	GPU_Line(screen, bx, by, bx, bh, edgeLightColor);
	GPU_Line(screen, bx, bh, bw, bh, edgeDarkColor);
	GPU_Line(screen, bw, by, bw, bh, edgeDarkColor);
	//GPU_Rectangle(screen, x, y, width, height, { 255,0,0,255 });
	//GPU_Rectangle(screen, x+1, y+1, width-1, height-1, { 0,0,255,255 });

	// Value
	if (sharedFont)
	{
		resManager->GetSharedFontResource(fontResID)->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
		resManager->GetSharedFontResource(fontResID)->DrawText(std::to_string(sliderValue) + " %", rw + 25.0f, y + 30.0f);
	}
	else
	{
		resManager->GetFontResource(fontResID)->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
		resManager->GetFontResource(fontResID)->DrawText(std::to_string(sliderValue) + " %", rw + 25.0f, y + 30.0f);
	}

	// Text
	if (sharedFont)
	{
		resManager->GetSharedFontResource(fontResID)->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
		resManager->GetSharedFontResource(fontResID)->DrawText(text, x + 25.0f, y + 30.0f);
	}
	else
	{
		resManager->GetFontResource(fontResID)->SetColor(textColor.r, textColor.g, textColor.b, textColor.a);
		resManager->GetFontResource(fontResID)->DrawText(text, x + 25.0f, y + 30.0f);
	}
}

void Slider::Event(SDL_Event &e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		if (drag)
		{
			// Move the slider button (part 1/2)
			bx = e.motion.x - 10.0f;
			
			// Clamp it
			if (bx < (rx - 10.0f))
				bx = rx - 10.0f;
			if (bx > (rw - 10.0f))
				bx = rw - 10.0f;

			// Move the slider button (part 2/2)
			bw = bx + 20.0f;

			// Update the slider value
			sliderValue = (int)(100.0f*(bx + 10.0f) / (rw - rx) - (rw - rx));
		}
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if ((e.motion.x >= bx) && (e.motion.x < bw) && (e.motion.y >= by) && (e.motion.y < bh))
		{
			SetEvent(Slider::SliderEventState::Down);
			drag = true;
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		SetEvent(Slider::SliderEventState::Up);
		drag = false;
		if ((e.motion.x >= bx) && (e.motion.x < bw) && (e.motion.y >= by) && (e.motion.y < bh))
		{
			SetClick(true);
		}
	}
	else if ((e.motion.x >= bx) && (e.motion.x < bw) && (e.motion.y >= by) && (e.motion.y < bh))
	{
		if (GetEvent() != SliderEventState::Down)
		{
			SetEvent(Slider::SliderEventState::Hover);
		}
	}
	else
	{
		SetEvent(Slider::SliderEventState::Up);
	}
}

void Slider::SetEvent(SliderEventState seState)
{
	this->sliderEventState = seState;
}

Slider::SliderEventState Slider::GetEvent()
{
	return sliderEventState;
}

void Slider::SetClick(bool click)
{
	this->click = click;
}

bool Slider::GetClick()
{
	return click;
}

void Slider::SetValue(int value)
{
	// Clamp it
	if (value < 0)
		value = 0;
	if (value > 100)
		value = 100;

	/*
	// Move the slider button (part 1/2)
	bx = e.motion.x - 10.0f;

	// Move the slider button (part 2/2)
	bw = bx + 20.0f;
	*/

	//sliderValue = (int)(100.0f*(bx + 10.0f) / (rw - rx) - (rw - rx));
	//
	//((sliderValue + (rw - rx))*(rw - rx))/100.0f - 10.0f = bx ;
	//

	// Update the slider value
	sliderValue = value;

	// Update the slider bar
	bx = ((sliderValue + (rw - rx))*(rw - rx)) / 100.0f - 10.0f;
	bw = bx + 20.0f;

}

int Slider::GetValue()
{
	return sliderValue;
}
