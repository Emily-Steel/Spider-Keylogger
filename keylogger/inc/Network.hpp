#ifndef _NETWORK_HPP_
# define _NETWORK_HPP_

# include <iostream>

typedef std::string APacket;

class Network
{
public:
	Network();
	~Network();

	bool connect(int port, std::string host);
	bool isConnected();

	Network &operator<<(APacket &packet);
	Network &operator>>(APacket &packet);

private:

};

#endif