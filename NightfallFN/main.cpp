#include "WebServer.hpp"
#include <Windows.h>
#include "Auth.hpp"
#include "CheatManager.hpp"
#include "Hooks.hpp"
#include "BuildTracker.hpp"
#include "HTML.hpp"
#include "WebsocketServer.hpp"

HMODULE GCM()
{
	HMODULE hModule = NULL;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)GCM, &hModule);
	return hModule;
}

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

	//Auth::promptKey();

	//system("cls");

	Keybinds::InitializeKeybinds();

	//BuildTracker::StartBuildTracker();

	//if (false)
	{
		CheatManager::ToggleCheat(NoRecoil);
		//CheatManager::ToggleCheat(BloomReducer);
		//CheatManager::ToggleCheat(RapidPickup);
	}

	// Let's start the WebSocket server
	auto wsServer = new WebSocketServer::NightfallWebSocketServer();
	wsServer->start();

	auto server = WebServer::NightfallServer();

	server.AddRoute("/", [](WebServer::NightfallServer* server, WebServer::ServerRoute* route) {
		server->SendRedirect("/home");
	});

	server.AddRoute("/home", [](WebServer::NightfallServer* server, WebServer::ServerRoute* route) {
		server->SendHTML("res/html/home.html");
	});

	server.RunServer();

	Hooks::SetupHooks();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Hooks::UnhookHooks();

	return 0;
}