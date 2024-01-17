#pragma once
#include "NightfallCheat.hpp"
#include "BuildTracker.hpp"

namespace NoRecoilSettings
{

}

void NoRecoilFunc()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!BuildTracker::bIsBuilding)
		{
			mouse_event(MOUSEEVENTF_MOVE, 0, 2, 0, 0);
		}
	}
}
auto NoRecoil = new NightfallCheat(NoRecoilFunc);