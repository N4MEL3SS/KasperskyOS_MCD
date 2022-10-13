#include "Server.hpp"

Server::Server(int port) : _port(port)
{
	this->_exit_flag = false;
}

Server::~Server() {}

void Server::InitServer()
{
	_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (_socket < 0)
	{
		std::cerr << "Error! Can't open socket for connections." << std::endl;
		exit(EXIT_FAILURE);
	}

	int yes = 1;
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_port);

	if (bind(_socket, (sockaddr*)&_address, sizeof(_address)) < 0)
	{
		std::cerr << "Error! Can't bind socket." << std::endl;
		exit(EXIT_FAILURE);
	}

	if (listen(_socket, FD_SETSIZE) < 0)
	{
		std::cerr << "Error! Listen failed." << std::endl;
		exit(EXIT_FAILURE);
	}

	if (setenv(ENV_PORT_NAME, std::to_string(_port).c_str(), 1) == -1)
	{
		std::cerr << "Error! Set env failed." << std::endl;
		exit(EXIT_FAILURE);
	}
	fcntl(_socket, F_SETFL, O_NONBLOCK);
}

void Server::AcceptConnection()
{
	size_t address_size = sizeof(_address);
	int new_connection_fd = accept(_socket, reinterpret_cast<sockaddr*>(&_address),
		reinterpret_cast<socklen_t *>(&address_size));

	if (new_connection_fd > 0)
	{
		struct pollfd pfd = {};
		pfd.fd = new_connection_fd;
		pfd.events = POLLIN;
		pfd.revents = 0;

		_user_fds.push_back(pfd);
		_user_reg_status[pfd.fd] = false;
		LOG(INFO) << "User: " << pfd.fd << " - Connected to server";
	}
}

void Server::WaitMsg()
{
	int user_fds_size = static_cast<int>(_user_fds.size());

	_current_connections = poll(_user_fds.data(), _user_fds.size(), 0);

	if (_current_connections > 0)
	{
		for (int i = 0; i < user_fds_size; i++)
		{
			if (_user_fds[i].revents & POLLIN)
			{
				std::string message = ReadMsg(_user_fds[i].fd);

				if (message == "STOP")
				{
					LOG(INFO) << "User: " << _user_fds[i].fd << " - Exit on server";
					_exit_flag = true;
					_user_reg_status.erase(_user_fds[i].fd);
					_user_fds.erase(_user_fds.begin() + i);
				}
				else if (!_user_reg_status[_user_fds[i].fd] && message == "START")
				{
					LOG(INFO) << "User: " << _user_fds[i].fd << " - Registered on server";
					_user_reg_status[_user_fds[i].fd] = true;
				}
				else if (_user_reg_status[_user_fds[i].fd])
					LOG(INFO) << "User: " << _user_fds[i].fd << " msg: " << message;
				else
					LOG(ERROR) << "User: " << _user_fds[i].fd \
						<< " - Violation of the interaction protocol";
			}
			_user_fds[i].revents = 0;
		}
	}
}

std::string Server::ReadMsg(int fd)
{
	std::string message;

	size_t bytesRead;
	char buff[512];

	memset(buff, '\0', 512);
	if ((bytesRead = recv(fd, buff, 512, 0)) > 0)
		message += buff;
	else if (bytesRead <= 0 && message.empty())
		return "STOP";

	size_t cnlr;

	if ((cnlr = message.find('\r', 0)) != std::string::npos)
		message = message.substr(0, cnlr);
	else if ((cnlr = message.find('\n', 0)) != std::string::npos)
		message = message.substr(0, cnlr);

	std::string result(message.begin(), message.end());

	return result;
}

bool Server::ServerState()
{
	if (_user_reg_status.empty() && _exit_flag)
	{
		unsetenv(ENV_PORT_NAME);
		return false;
	}
	return true;
}
