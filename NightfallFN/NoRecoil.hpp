#pragma once
#include "NightfallCheat.hpp"

void NoRecoilFunc()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		mouse_event(MOUSEEVENTF_MOVE, 0, 2, 0, 0);
	}
}
auto NoRecoil = NightfallCheat(NoRecoilFunc);