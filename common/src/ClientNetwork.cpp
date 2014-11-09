#include "ClientNetwork.hpp"

#include "BoostConnectSocket.hpp" //ToRemove Factory

ClientNetwork::ClientNetwork()
: _connect(false)
{
	_socket = std::unique_ptr<IConnectSocket>(new BoostConnectSocket(_ios)); //AFactory<IConnectSocket>::instance().create("BoostConnectSocket");
}

ClientNetwork::~ClientNetwork()
{
    
}

bool ClientNetwork::connect(int port, std::string host, const std::string &id)
{
	if (!_socket->connect(host, port))
		_connect = false;
	else
	{
		int version = 0xFF000000;

		_socket->write(&version, sizeof(version));
		_socket->write(id.c_str(), id.size() + 1);
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
    catch (std::runtime_error &e)
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
    catch (std::runtime_error &e)
    {
        _connect = false;
    }
    return (*this);
}
