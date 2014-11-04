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
        _connect = false;
        return (false);
    }
    _connect = true;
    return (true);
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
