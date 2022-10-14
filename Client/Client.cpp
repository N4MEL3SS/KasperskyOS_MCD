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
	if (msg.find('\n', 0) == std::string::npos)
		msg.push_back('\n');
	const char *msg_char = msg.c_str();

	if (send(_socket, msg_char, strlen(msg_char), 0) > 0)
	{
		char buf;
		while (recv(_socket, &buf, 1, 0) < 0) {}
	}
}

void Client::StartMsg()
{
	SendMsg("START");
	std::cout << "The user is registered on the server" << std::endl;
}

void Client::StopMsg()
{
	SendMsg("STOP");
	std::cout << "All message have been sent" << std::endl;
}
