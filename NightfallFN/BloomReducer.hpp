#pragma once
#include "NightfallCheat.hpp"

bool bShouldReduce = true;
void BloomReducerFunc()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (bShouldReduce)
		{
			mouse_event(MOUSEEVENTF_MOVE, 0, 4, 0, 0);
			bShouldReduce = false;
		}
	}
	else
		bShouldReduce = true;
}
auto BloomReducer = new NightfallCheat(BloomReducerFunc);