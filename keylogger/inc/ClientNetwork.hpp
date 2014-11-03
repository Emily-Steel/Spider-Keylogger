#ifndef _NETWORK_HPP_
# define _NETWORK_HPP_

# include <iostream>
# include "APacket.hpp"
# include "ASocket.hpp"

class Network
{
public:
	Network();
	~Network();

	bool connect(int port, std::string host);
	bool isConnected();

	Network &operator<<(const APacket &packet);
	Network &operator>>(APacket &packet);

private:
    ASocket *_socket;
    bool    _connect;
};

#endif