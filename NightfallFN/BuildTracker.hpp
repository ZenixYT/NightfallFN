#pragma once
#include "Keybinds.hpp"
#include <thread>

namespace BuildTracker
{
	bool bIsBuilding = false;
	void BuildTrackerFunc()
	{
		while (true)
		{
			if (GetAsyncKeyState(Keybinds::GetKeyFromKeybindType("BUILD_WALL")))
				bIsBuilding = true;

			if (GetAsyncKeyState(Keybinds::GetKeyFromKeybindType("BUILD_FLOOR")))
				bIsBuilding = true;

			if (GetAsyncKeyState(Keybinds::GetKeyFromKeybindType("BUILD_STAIR")))
				bIsBuilding = true;

			if (GetAsyncKeyState(Keybinds::GetKeyFromKeybindType("BUILD_PYRAMID")))
				bIsBuilding = true;

			if (GetAsyncKeyState(Keybinds::GetKeyFromKeybindType("BUILD_TRAP")))
				bIsBuilding = true;

			// Slots
			if (GetAsyncKeyState(Keybinds::GetKeyFromKeybindType("SLOT_ONE")))
				bIsBuilding = false;

			if (GetAsyncKeyState(Keybinds::GetKeyFromKeybindType("SLOT_TWO")))
				bIsBuilding = false;

			if (GetAsyncKeyState(Keybinds::GetKeyFromKeybindType("SLOT_THREE")))
				bIsBuilding = false;

			if (GetAsyncKeyState(Keybinds::GetKeyFromKeybindType("SLOT_FOUR")))
				bIsBuilding = false;

			if (GetAsyncKeyState(Keybinds::GetKeyFromKeybindType("SLOT_FIVE")))
				bIsBuilding = false;

			if (GetAsyncKeyState(Keybinds::GetKeyFromKeybindType("SLOT_SIX")))
				bIsBuilding = false;
		}
	}

	void StartBuildTracker()
	{
		std::thread BuildTrackerThread(BuildTrackerFunc);
		BuildTrackerThread.detach();
	}
}