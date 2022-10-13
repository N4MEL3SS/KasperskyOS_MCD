#include "Server.hpp"

INITIALIZE_EASYLOGGINGPP

int main()
{
	signal(SIGPIPE, SIG_IGN);

	Server Server(6667);

	Server.InitServer();

	while (Server.ServerState())
	{
		Server.AcceptConnection();
		Server.WaitMsg();
	}

	return 0;
}
