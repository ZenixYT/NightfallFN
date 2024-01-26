//#include "WebServer.hpp"
#include <Windows.h>
#include "Auth.hpp"
#include "CheatManager.hpp"
#include "Hooks.hpp"
#include "BuildTracker.hpp"

int main()
{
	/*
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

	Keybinds::InitializeKeybinds();

	//BuildTracker::StartBuildTracker();

	//if (false)
	{
		CheatManager::ToggleCheat(NoRecoil);
		CheatManager::ToggleCheat(BloomReducer);
		CheatManager::ToggleCheat(RapidPickup);
	}

	Hooks::SetupHooks();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Hooks::UnhookHooks();
	*/

	/*
	auto server = WebServer::NightfallServer();
	
	// Add routing here
	server.AddRoute("/", [](WebServer::NightfallServer* server, char* args[]) {
		server->SendResponse("<html><h1>Home</h1></html>");
	});

	server.AddRoute("/lol", [](WebServer::NightfallServer* server, char* args[]) {
		server->SendResponse("<html><h1>Lol</h1></html>");
	});
	
	server.RunServer();
	*/

	std::string lol = "/lol?name=Anthony?pass=12345";
	
	size_t startPos = lol.find("?");
	std::string paramsString = lol.substr(startPos + 1);

	std::cout << paramsString << std::endl;

	return 0;
}