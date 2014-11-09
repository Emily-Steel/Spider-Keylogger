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
		int version = 0x312E3076;
		std::vector<uint8_t> result;
		HandshakeResult test;

		_socket->write(&version, sizeof(version));
		_socket->write(id.c_str(), id.size() + 1);
		_socket->read(result, 10);
		try
		{
			test.from_bytes(result);
			_connect = true;
		}
		catch (std::runtime_error &e)
		{
			_connect = false;
		}
	}
	return (_connect);
}

bool ClientNetwork::isConnected() const
{
    return (_connect);
}

ClientNetwork &ClientNetwork::operator<<(const APacket &packet)
{
	if (_socket->isConnected())
		(*_socket) << packet;
	else
        _connect = false;
    return (*this);
}

ClientNetwork &ClientNetwork::operator>>(APacket &packet)
{
	if (_socket->isConnected())
		(*_socket) >> packet;
	else
		_connect = false;
	return (*this);
}
