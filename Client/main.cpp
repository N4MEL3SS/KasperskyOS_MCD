#include "Client.hpp"

int main()
{
//	char *port_char;
//	if ((port_char = getenv(ENV_PORT_NAME)) == nullptr)
//	{
//		std::cerr << "Error! Get Port from env failed." << std::endl;
//		exit(EXIT_FAILURE);
//	}
//	Client Client(atoi(port_char));
	Client Client(6667);

	Client.InitClient();

	Client.StartMsg();

	Client.SendMsg("Hi\n");
	Client.SendMsg("Test\n");
	Client.SendMsg("Just\n");
	Client.SendMsg("Work\n");

	Client.StopMsg();

	return 0;
}
