#pragma once
#include "NightfallCheat.hpp"

#define PICKUP_SPAM_KEY 0x4C
#define PICKUP_KEY 0x45

bool bSpamKey = false;

void RapidPickupFunc()
{
	if (GetAsyncKeyState(PICKUP_KEY) & 0x8000)
	{
        INPUT inputs[2] = {};

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = PICKUP_SPAM_KEY;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = PICKUP_SPAM_KEY;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

        SendInput(2, inputs, sizeof(INPUT));
	}
}
auto RapidPickup = new NightfallCheat(RapidPickupFunc);