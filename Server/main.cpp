#include "Server.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
	signal(SIGPIPE, SIG_IGN);

	int port;

	if (argc == 2 && std::isdigit(*argv[1]))
		port = atoi(argv[1]);
	else
		port = 6667;

	Server Server(port);

	Server.InitServer();
	while (Server.ServerState())
	{
		Server.AcceptConnection();
		Server.WaitMsg();
	}

	return 0;
}
