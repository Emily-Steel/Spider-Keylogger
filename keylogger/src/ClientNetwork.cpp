#include "ClientNetwork.hpp"

ClientNetwork::ClientNetwork()
: _connect(false)
{
    
}

ClientNetwork::~ClientNetwork()
{
    
}

bool ClientNetwork::connect(int port, std::string host)
{
	if (!_socket->connect(host, port))
	{
		char data[] = "salut";
		_socket->write(data, 5);
		_connect = false;
	}
	else
		_connect = true;
	return (_connect);
}

bool ClientNetwork::isConnected()
{
    return (_connect);
}

ClientNetwork &ClientNetwork::operator<<(const APacket &packet)
{
    try {
        (*_socket) << packet;
    }
    catch (std::runtime_error e)
    {
        _connect = false;
    }
    return (*this);
}

ClientNetwork &ClientNetwork::operator>>(APacket &packet)
{
    try {
        (*_socket) >> packet;
    }
    catch (std::runtime_error e)
    {
        _connect = false;
    }
    return (*this);
}
