#include "Client.hpp"

Client::Client(int port) : _port(port) {}

Client::~Client() {}

void Client::InitClient()
{
	_socket = socket(AF_INET, SOCK_STREAM, 0); // создание TCP-сокета

	if (_socket < 0)
	{
		std::cerr << "Error! Can't open socket for connections." << std::endl;
		exit(EXIT_FAILURE);
	}

	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_port);

	if (connect(_socket, (sockaddr *)&_address, sizeof(_address)) < 0)
	{
		std::cerr << "Error! Connections failed." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Client::SendMsg(std::string msg)
{
	write(_socket, msg.c_str(), msg.size());
}

void Client::StartMsg()
{
	write(_socket, "START\n", 6);
}

void Client::StopMsg()
{
	write(_socket, "STOP\n", 5);
}
