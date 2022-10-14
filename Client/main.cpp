#include "Client.hpp"

int main(int argc, char *argv[])
{
	char *port_char;
	if ((port_char = getenv(ENV_PORT_NAME)) == nullptr)
	{
		std::cerr << "Error! Get Port from env failed." << std::endl;
		exit(EXIT_FAILURE);
	}

	Client Client(atoi(port_char));
	std::string msg;

	(void)argv;
	Client.InitClient();

	Client.StartMsg();

	if (argc == 1)
	{
		Client.SendMsg("It");
		Client.SendMsg("Just");
		Client.SendMsg("Works!");
	}
	else
	{
		while (std::cin >> msg && msg != "STOP")
			Client.SendMsg(msg);
	}

	Client.StopMsg();

	return 0;
}
