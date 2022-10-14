#include <pthread.h>
#include "Server.hpp"

INITIALIZE_EASYLOGGINGPP

int port;

void *server_start(void *)
{
	signal(SIGPIPE, SIG_IGN);

	Server Server(port);

	Server.InitServer();
	while (Server.ServerState())
	{
		Server.AcceptConnection();
		Server.WaitMsg();
	}
	return nullptr;
}

int main(int argc, char *argv[])
{
	pthread_t work_thread;

	if (argc == 2 && std::isdigit(*argv[1]))
		port = atoi(argv[1]);
	else
		port = 6667;

	pthread_create(&work_thread, NULL, server_start, &port);
	pthread_join(work_thread, NULL);

	return 0;
}
