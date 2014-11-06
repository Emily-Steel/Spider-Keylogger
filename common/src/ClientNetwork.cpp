#include "ClientNetwork.hpp"

ClientNetwork::ClientNetwork()
: _connect(false)
{
	_socket = new BoostSocket();
}

ClientNetwork::~ClientNetwork()
{
    
}

bool ClientNetwork::connect(int port, std::string host)
{
	if (!_socket->connect(host, port))
		_connect = false;
	else
	{
		char data[] = "salut";
		_socket->write(data, 5);
		_connect = true;
	}
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
