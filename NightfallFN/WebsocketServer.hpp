#pragma once
#define PORT 90

#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "JSONParser.hpp"

// copied from a previous project LMFAO
namespace WebSocketServer
{
	class NightfallWebSocketServer
	{
	public:
		NightfallWebSocketServer()
		{
			this->server.init_asio();

			this->server.set_message_handler(bind(&NightfallWebSocketServer::on_message, this, std::placeholders::_1, std::placeholders::_2));
			//this->wsServer.set_open_handler(bind(&GalileoServer::on_open, this, std::placeholders::_1));
			//this->wsServer.set_close_handler(bind(&GalileoServer::on_close, this, std::placeholders::_1));
		}

		// explicitly delete copy constructor
		NightfallWebSocketServer(const NightfallWebSocketServer&) = delete;

		void start()
		{
			this->server.listen(PORT);
			this->server.start_accept();

			auto lambda = [&]() { this->server.run(); };
			std::thread runThread(lambda);
			runThread.detach();

			std::cout << "Opened websocket server on port " << PORT << std::endl;
		}

	private:
		websocketpp::server<websocketpp::config::asio> server;

		void on_message(websocketpp::connection_hdl hdl, websocketpp::server<websocketpp::config::asio>::message_ptr msg)
		{
			std::string sMsg = msg->get_payload();

			JSONParser::ParseJSON(sMsg);
		}
	};
};