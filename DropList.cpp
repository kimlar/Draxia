#include "DropList.h"

DropList::DropList(StateManager* stateManager, ResID fontResID, std::string label, float x, float y, bool sharedFont) : stateManager(stateManager), fontResID(fontResID), label(label), x(x), y(y), sharedFont(sharedFont)
{
	resManager = stateManager->GetResourceManager();
	screen = stateManager->GetGpuTarget();

	width = x + 300.0f;
	height = y + 60.0f;

	dlx = width;
	dly = y;
	dlw = width + 350.0f;
	dlh = y + 60.0f;

	btx = dlw - 60.0f;
	bty = dly = y;
	btw = dlw;
	bth = dlh;

	edgeLightColor = { 127, 127, 127, 255 };
	edgeDarkColor = { 27, 27, 27, 255 };
	fillColor = { 55, 55, 55, 255 };
	labelColor = { 255, 255, 255, 255 };
	listColor = { 255, 255, 255, 255 };
	listSelectionColor = { 0, 0, 255, 255 };

	click = false;
	showList = false;
	vListItemSelected = -1; // Not selected

	// Mouse
	mx = 0;
	my = 0;
	mouseHoverSelect = -1;
}

DropList::~DropList()
{
	Free();
}

void DropList::Free()
{
	vList.clear();

	resManager = nullptr;
	stateManager = nullptr;
	screen = nullptr;
}

void DropList::Draw()
{
	// DropList
	GPU_Rectangle(screen, dlx, dly, dlw, dlh, edgeLightColor);

	// Text
	if (sharedFont)
	{
		resManager->GetSharedFontResource(fontResID)->SetColor(listColor.r, listColor.g, listColor.b, listColor.a);
		if (vListItemSelected != -1)
			resManager->GetSharedFontResource(fontResID)->DrawText(vList[vListItemSelected], dlx + 25.0f, dly + 30.0f);
	}
	else
	{
		resManager->GetFontResource(fontResID)->SetColor(listColor.r, listColor.g, listColor.b, listColor.a);
		if (vListItemSelected != -1)
			resManager->GetFontResource(fontResID)->DrawText(vList[vListItemSelected], dlx + 25.0f, dly + 30.0f);
	}

	// Drop Button
	GPU_RectangleFilled(screen, btx, bty, btw, bth, fillColor);
	GPU_Line(screen, btx, bty, btw, bty, edgeLightColor);
	GPU_Line(screen, btx, bty, btx, bth, edgeLightColor);
	GPU_Line(screen, btx, bth, btw, bth, edgeLightColor);
	GPU_Line(screen, btw, bty, btw, bth, edgeLightColor);

	if (showList)
	{
		GPU_Line(screen, btx + 1, bty + 1, btw - 1, bty + 1, edgeDarkColor);
		GPU_Line(screen, btx + 1, bty + 1, btx + 1, bth - 1, edgeDarkColor);
		GPU_Line(screen, btx + 1, bth - 1, btw - 1, bth - 1, edgeLightColor);
		GPU_Line(screen, btw - 1, bty + 1, btw - 1, bth - 1, edgeLightColor);
		GPU_TriFilled(screen, btx + 10.0f, bty + 15.0f, btw - 10.0f, bty + 15.0f, btx + (btw-btx)/2, bty + (bth-bty)*0.707f, { 224, 224, 224, 255 });
		GPU_Tri(screen, btx + 10.0f, bty + 16.0f, btw - 10.0f, bty + 16.0f, btx + (btw - btx) / 2, bty + (bth - bty)*0.707f, { 0, 0, 0, 255 });
	}
	else
	{
		GPU_Line(screen, btx + 1, bty + 1, btw - 1, bty + 1, edgeLightColor);
		GPU_Line(screen, btx + 1, bty + 1, btx + 1, bth - 1, edgeLightColor);
		GPU_Line(screen, btx + 1, bth - 1, btw - 1, bth - 1, edgeDarkColor);
		GPU_Line(screen, btw - 1, bty + 1, btw - 1, bth - 1, edgeDarkColor);
		GPU_TriFilled(screen, btx + 10.0f, bty + 15.0f, btw - 10.0f, bty + 15.0f, btx + (btw - btx) / 2, bty + (bth - bty)*0.707f, { 191, 191, 191, 255 });
		GPU_Tri(screen, btx + 10.0f, bty + 16.0f, btw - 10.0f, bty + 16.0f, btx + (btw - btx) / 2, bty + (bth - bty)*0.707f, { 0, 0, 0, 255 });
	}

	if (showList)
	{
		GPU_RectangleFilled(screen, dlx, dlh, dlw, dlh + 15.0f + vList.size()*45, edgeDarkColor);
		GPU_Rectangle(screen, dlx, dlh, dlw, dlh + 15.0f + vList.size() * 45, edgeLightColor);

		// Draw the mouse hover selection (blue bar)
		mouseHoverSelect = -1;
		if ((mx >= dlx) && (mx < dlw) && (my >= dlh) && (my < dlh + 15.0f + vList.size() * 45.0f + 35.0f))
		{
			for (int i = 0; i < vList.size(); i++)
			{
				if ((my >= dlh + 10.0f + i * 45.0f) && (my < dlh + 15.0f + i * 45.0f + 35.0f))
				{
					mouseHoverSelect = i;
					GPU_RectangleFilled(screen, dlx + 1, dlh + 10.0f + i * 45.0f, dlw - 1, dlh + 15.0f + i * 45.0f + 35.0f, listSelectionColor);
					break;
				}
			}
		}

		// Draw all the text in the list
		for (int i = 0; i < vList.size(); i++)
		{
			if (sharedFont)
			{
				if (vListItemSelected == i)
					resManager->GetSharedFontResource(fontResID)->SetColor(255, 255, 255, 255);
				else
					resManager->GetSharedFontResource(fontResID)->SetColor(171, 171, 171, 255);
				resManager->GetSharedFontResource(fontResID)->DrawText(vList[i], dlx + 25.0f, dly + 90.0f + i*45.0f);
			}
			else
			{
				if (vListItemSelected == i)
					resManager->GetFontResource(fontResID)->SetColor(255, 255, 255, 255);
				else
					resManager->GetFontResource(fontResID)->SetColor(171, 171, 171, 255);
				resManager->GetFontResource(fontResID)->DrawText(vList[i], dlx + 25.0f, dly + 90.0f + i*45.0f);
			}

		}
	}

	// Label
	if (sharedFont)
	{
		resManager->GetSharedFontResource(fontResID)->SetColor(labelColor.r, labelColor.g, labelColor.b, labelColor.a);
		resManager->GetSharedFontResource(fontResID)->DrawText(label, x + 25.0f, y + 30.0f);
	}
	else
	{
		resManager->GetFontResource(fontResID)->SetColor(labelColor.r, labelColor.g, labelColor.b, labelColor.a);
		resManager->GetFontResource(fontResID)->DrawText(label, x + 25.0f, y + 30.0f);
	}
}

void DropList::Event(SDL_Event &e)
{

	if (e.type == SDL_MOUSEMOTION)
	{
		// Keep mouse coords for internal use
		mx = e.motion.x;
		my = e.motion.y;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if ((e.motion.x >= dlx) && (e.motion.x < dlw) && (e.motion.y >= dly) && (e.motion.y < dlh))
		{
			SetEvent(DropList::DropListEventState::Down);
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		SetEvent(DropList::DropListEventState::Up);
		// User clicked in the list
		if (showList)
		{
			if ((mx >= dlx) && (mx < dlw) && (my >= dlh) && (my < dlh + 15.0f + vList.size() * 45.0f + 35.0f))
			{
				if (mouseHoverSelect != -1)
				{
					SetClick(true);
					vListItemSelected = mouseHoverSelect;
					showList = false;
				}
			}
		}

		// User clicked on the main box
		if ((e.motion.x >= dlx) && (e.motion.x < dlw) && (e.motion.y >= dly) && (e.motion.y < dlh))
		{
			SetClick(true);
			showList = !showList;
		}

		// If user clicks outside of the list when it is showing, then we need to hide the list.
		if ((e.motion.x < dlx) || (e.motion.x > dlw) || (e.motion.y < dly) || (e.motion.y > dlh + 15.0f + vList.size() * 45))
			showList = false;
	}
	else if ((e.motion.x >= dlx) && (e.motion.x < dlw) && (e.motion.y >= dly) && (e.motion.y < dlh))
	{
	}
	else
	{
		SetEvent(DropList::DropListEventState::Up);
	}
}

void DropList::SetEvent(DropListEventState dleState)
{
	this->dropListEventState = dleState;
}

DropList::DropListEventState DropList::GetEvent()
{
	return dropListEventState;
}

void DropList::SetClick(bool click)
{
	this->click = click;
}

bool DropList::GetClick()
{
	return click;
}

void DropList::SetShowList(bool show)
{
	this->showList = show;
}

bool DropList::GetShowList()
{
	return showList;
}

bool DropList::EscIsPressed()
{
	if (showList)
	{
		showList = false;
		return true; // The list was open
	}
	return false; // This list was not open, so it nothing for this UI-control to concern about.
}

void DropList::AddItem(std::string item)
{
	vList.push_back(item);
}

void DropList::SetItemSelectedByText(std::string ItemText)
{
	for (int i = 0; i < vList.size(); i++)
	{
		if (vList[i] == ItemText)
		{
			vListItemSelected = i;
			break;
		}
	}
}

std::string DropList::GetItemSelected()
{
	if (vListItemSelected == -1)
		return "";
	if (vList.size() == 0 || vList.size() < vListItemSelected)
		return "";
	return vList.at(vListItemSelected);
}
