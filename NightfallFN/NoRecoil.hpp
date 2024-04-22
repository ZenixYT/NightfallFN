#pragma once
#include "NightfallCheat.hpp"
#include "BuildTracker.hpp"

DWORD recoilMag = 2;

void NoRecoilFunc()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!BuildTracker::bIsBuilding)
		{
			mouse_event(MOUSEEVENTF_MOVE, 0, recoilMag, 0, 0);
		}
	}
}
auto NoRecoil = new NightfallCheat(NoRecoilFunc);