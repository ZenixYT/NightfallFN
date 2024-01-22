#pragma once
#include "NightfallCheat.hpp"
#include "BuildTracker.hpp"

namespace BloomReducerSettings
{
	int mickeysToMove = 20;
}

bool bShouldReduce = true;
void BloomReducerFunc()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (bShouldReduce && !BuildTracker::bIsBuilding)
		{
			mouse_event(MOUSEEVENTF_MOVE, 0, (DWORD)BloomReducerSettings::mickeysToMove, 0, 0);
			bShouldReduce = false;
		}
	}
	else
		bShouldReduce = true;
}
auto BloomReducer = new NightfallCheat(BloomReducerFunc);