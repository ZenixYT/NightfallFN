#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>

#define PORT 80		

namespace WebServer
{
	class NightfallServer
	{
	public:
		NightfallServer()
		{
			if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			{
				std::cerr << "Could not initialize WSA!" << std::endl;
			}

			this->webSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (this->webSocket == INVALID_SOCKET)
			{
				std::cerr << "Could not create socket!" << std::endl;
			}

			// Now, we bind the socket to the address (localhost)
			server.sin_family = AF_INET;
			server.sin_addr.s_addr = inet_addr("127.0.0.1");
			server.sin_port = PORT;
			server_len = sizeof(server);

			if (bind(this->webSocket, (SOCKADDR*)&server, server_len) != 0)
			{
				std::cerr << "Could not bind socket!" << std::endl;
			}

			if (listen(this->webSocket, 25) != 0)
			{
				std::cerr << "Could not start listening!" << std::endl;
			}

			std::cout << "Nightfall server listening on port " << PORT << "!" << std::endl; // Replace this by opening the server

			int reqInfo = 0;
			while (true)
			{
				this->acceptSocket = accept(this->webSocket, (SOCKADDR*)&server, &server_len);
				if (this->acceptSocket == INVALID_SOCKET)
				{
					std::cerr << "Could not accept request!" << std::endl;
					continue;
				}

				char buff[30720] = { 0 };
				reqInfo = recv(this->acceptSocket, buff, BUFFER_SIZE, 0);
				if (reqInfo < 0)
					continue;

				// sample response (taken from tutorial)
				std::string serverMessage = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
				std::string response = "<html><h1>Hello World!</h1></html>";
				
				serverMessage.append(std::to_string(response.size()));
				serverMessage.append("\n\n");
				serverMessage.append(response);

				int bytesSent = 0;
				int totalBytesSent = 0;
				while (bytesSent < totalBytesSent)
				{
					bytesSent = send(this->acceptSocket, serverMessage.c_str(), serverMessage.size(), 0);
					if (bytesSent < 0)
						std::cerr << "Could not send response!" << std::endl;

					totalBytesSent += bytesSent;
				}
				std::cout << "Sent response to client!" << std::endl;

				closesocket(this->acceptSocket);
			}
		}
	private:
		SOCKET webSocket;
		SOCKET acceptSocket;
		WSADATA wsaData;
		struct sockaddr_in server;
		int server_len;
		int BUFFER_SIZE = 37020;

	};
}