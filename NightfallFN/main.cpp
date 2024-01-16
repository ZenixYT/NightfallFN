#include <iostream>
#include <Windows.h>
#include "Auth.hpp"
#include "CheatManager.hpp"

int main()
{
	SetConsoleTitleA("Nightfall");

	std::cout << R"(
 _______   .__         .__      __     _____         .__   .__   
 \      \  |__|  ____  |  |__ _/  |_ _/ ____\_____   |  |  |  |  
 /   |   \ |  | / ___\ |  |  \\   __\\   __\ \__  \  |  |  |  |  
/    |    \|  |/ /_/  >|   Y  \|  |   |  |    / __ \_|  |__|  |__
\____|__  /|__|\___  / |___|  /|__|   |__|   (____  /|____/|____/
        \/    /_____/       \/                    \/             
)" << std::endl;

	Auth::promptKey();

	system("cls");

	bool bRightShiftPressed = false;
	while (true)
	{
		if (GetAsyncKeyState(VK_RSHIFT) & 0x8000)
		{
			if (!bRightShiftPressed)
			{
				CheatManager::ToggleCheat(NoRecoil);
				CheatManager::ToggleCheat(BloomReducer);
				CheatManager::ToggleCheat(RapidPickup);
				bRightShiftPressed = true;

				if (NoRecoil->bIsCheatEnabled)
					std::cout << "[NIGHTFALL] Cheats Enabled!" << std::endl;
				else
					std::cout << "[NIGHTFALL] Cheats Disabled!" << std::endl;
			}
		}
		else
			bRightShiftPressed = false;
	}

	return 0;
}