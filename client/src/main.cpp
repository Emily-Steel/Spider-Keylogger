#include <iostream>
#include "ClientLogger.hpp"

int	main(int ac, char **av)
{
	ClientLogger client;

	if (!client.init(av[0]))
	{
		std::cerr << GetLastError() << std::endl;
		Sleep(1000);
		return (1);
	}
	client.run();
	return (0);
}