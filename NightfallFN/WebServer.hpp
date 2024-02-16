#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <thread>
#include <functional>
#include "Utils.hpp"

#define PORT 80

namespace WebServer
{
	namespace ServerUtils
	{
		std::map<std::string, std::string> ParseParametersFromRoute(std::string route)
		{
			auto params = Utils::splitString(Utils::splitString(route, '?')[1], '&');
			std::map<std::string, std::string> toRet;

			for (int i = 0; i < params.size(); i++)
			{
				auto param = Utils::splitString(params[i], '=');
				toRet.insert({param[0], param[1]});
			}

			return toRet;
		}
	}

	struct ServerRoute
	{
		std::string routeName;
		std::vector<std::string> argv;
	};

	class NightfallServer
	{
	public:
		NightfallServer()
		{
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			{
				std::cout << "Could not initialize WSA!" << std::endl;
			}

			this->webSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (this->webSocket == INVALID_SOCKET)
			{
				std::cout << "Could not create socket!" << std::endl;
			}

			// Now, we bind the socket to the address (localhost)
			server.sin_family = AF_INET;
			server.sin_addr.s_addr = INADDR_ANY;
			server.sin_port = htons(PORT);
			server_len = sizeof(server);

			if (bind(this->webSocket, (SOCKADDR*)&server, server_len) != 0)
			{
				std::cout << "Could not bind socket!" << std::endl;
			}

			if (listen(this->webSocket, SOMAXCONN) != 0)
			{
				std::cout << "Could not start listening!" << std::endl;
			}
		}

		void RunServer()
		{
			std::thread runThread([this]() {
				std::cout << "Nightfall server listening on port " << PORT << "!" << std::endl; // Replace this by opening the server

				int reqInfo = 0;
				while (true)
				{
					this->acceptSocket = accept(this->webSocket, (SOCKADDR*)&server, &server_len);
					if (this->acceptSocket == INVALID_SOCKET)
					{
						std::cout << "Could not accept request!" << std::endl;
						continue;
					}

					char buff[30720] = { 0 };
					reqInfo = recv(this->acceptSocket, buff, BUFFER_SIZE, 0);
					if (reqInfo < 0)
					{
						std::cout << "Could not read request!" << std::endl;
						continue;
					}

					std::string request = buff;
					size_t start = request.find(" ") + 1;
					size_t end = request.find(" ", start);
					std::string route = request.substr(start, end - start);
					std::cout << route << std::endl;

					// sample response
					auto params = ServerUtils::ParseParametersFromRoute(route);
					
					//this->SendResponse("<html><h1>Whoops!\nThe page you were looking for wasn't found!</h1></html>");

					closesocket(this->acceptSocket);
				}
			});
			runThread.join();
		}

		void SendResponse(const std::string& response)
		{
			std::string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
			
			serverMessage.append(std::to_string(response.size()));
			serverMessage.append("\n\n");
			serverMessage.append(response);

			int bytesSent = 0;
			int totalBytesSent = 0;
			while (bytesSent < serverMessage.size())
			{
				bytesSent = send(this->acceptSocket, serverMessage.c_str(), serverMessage.size(), 0);
				if (bytesSent < 0)
					std::cout << "Could not send response!" << std::endl;

				totalBytesSent += bytesSent;
			}
			std::cout << "Sent response to client!" << std::endl;
		}

		ServerRoute* PingRoute(std::string route)
		{
			auto params = ServerUtils::ParseParametersFromRoute(route);
			auto routeName = Utils::splitString(route, '?')[0];


			for (auto& entry : routeMap)
			{
				if (entry.first->routeName == route)
				{
					return entry.first;
				}
			}

			return nullptr;
		}

		std::function<void(NightfallServer*, ServerRoute*)> GetCallbackFromRoute(ServerRoute* route)
		{
			auto it = routeMap.find(route);
			if (it != routeMap.end())
				return it->second;
		}

		void AddRoute(std::string route, std::function<void(NightfallServer*, ServerRoute*)> routeCallback)
		{
			ServerRoute srRoute;

			if (route.find("?") != std::string::npos)
			{
				srRoute.routeName = Utils::splitString(route, '?')[0];
			
				auto params = Utils::splitString(srRoute.routeName, '&');
				for (int i = 0; i < params.size(); i++)
				{
					if (params[i].find("=") != std::string::npos)
						srRoute.argv.push_back(Utils::splitString(params[i], '=')[0]);
				}
			}
			else
				srRoute.routeName = route;

			routeMap.insert({ &srRoute, routeCallback });
		}
	private:
		SOCKET webSocket;
		SOCKET acceptSocket;
		WSADATA wsaData;
		struct sockaddr_in server;
		int server_len;
		int BUFFER_SIZE = 30720;
		bool bIsRunning = false;
		std::map<ServerRoute*, std::function<void(NightfallServer*, ServerRoute*)>> routeMap;
	};
}