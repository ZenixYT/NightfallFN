#pragma once
#include "NoRecoil.hpp"
#include "BloomReducer.hpp"
#include "RapidPickup.hpp"

namespace CheatManager
{
	void ToggleCheat(NightfallCheat* cheatToToggle)
	{
		if (cheatToToggle->bIsCheatEnabled)
			cheatToToggle->StopCheat();
		else
			cheatToToggle->StartCheat();
	}
}