#pragma once
#define PORT 90

#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

namespace WebSocketServer
{
	void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg)
	{
		std::cout << msg->get_payload() << std::endl;
	}

	int StartServer()
	{
		server wsServer;

		wsServer.set_message_handler(&on_message);
		wsServer.set_access_channels(websocketpp::log::alevel::all);
		wsServer.set_error_channels(websocketpp::log::elevel::all);

		wsServer.init_asio();
		wsServer.listen(PORT);
		wsServer.start_accept();

		wsServer.run();
	}
}