#include <iostream>
#include <Windows.h>
#include "Auth.hpp"

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

	while (true) {}

	return 0;
}