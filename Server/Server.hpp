#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

#include "easylogging++.h"

#define ENV_PORT_NAME "KASPER_TEST_PORT"

class Server
{
 private:
	std::vector<struct pollfd> _user_fds;
	std::map<int, bool> _user_reg_status;
	sockaddr_in _address{};
	int			_socket{};
	int			_port;
	int			_current_connections{};
	bool		_exit_flag;

 public:
	Server(int port);
	~Server();

	bool ServerState();

	void InitServer();
	void AcceptConnection();
	void WaitMsg();
	static std::string ReadMsg(int fd);
	void SendStatus(int fd);
};

#endif //SERVER_HPP
