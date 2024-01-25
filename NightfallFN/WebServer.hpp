#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <functional>

#define PORT 8080

namespace WebServer
{
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

					// sample response (taken from tutorial)
					SendResponse("<html><h1>Hello World!</h1></html>");

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

		void AddRoute(std::string route, std::function<void(NightfallServer*, char*[])> routeCallback)
		{
			this->routeMap[route] = routeCallback;
		}
	private:
		SOCKET webSocket;
		SOCKET acceptSocket;
		WSADATA wsaData;
		struct sockaddr_in server;
		int server_len;
		int BUFFER_SIZE = 30720;
		bool bIsRunning = false;
		std::map<std::string, std::function<void(NightfallServer*, char*[])>> routeMap{};
	};
}