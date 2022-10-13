#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

#define ENV_PORT_NAME "KASPER_TEST_PORT"

class Client
{
 private:
	sockaddr_in _address{};
	int			_socket{};
	int			_port;
 public:
	Client(int port);
	~Client();

	void InitClient();
	void SendMsg(std::string msg);
	void StartMsg();
	void StopMsg();
};

#endif //CLIENT_HPP
