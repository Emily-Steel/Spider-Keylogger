#include "Network.hpp"

Network::Network()
: _connect(false)
{
    
}

Network::~Network()
{
    
}

bool Network::connect(int port, std::string host)
{
    if (!_socket->connect(host, port))
    {
        _connect = false;
        return (false);
    }
    _connect = true;
    return (true);
}

bool Network::isConnected()
{
    return (_connect);
}

Network &Network::operator<<(const APacket &packet)
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

Network &Network::operator>>(APacket &packet)
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
