#include "BoostConnectSocket.hpp"

//AFactoryRegistration<IConnectSocket, BoostConnectSocket> boostConnectSocketFactReg("BoostConnectSocket");

BoostConnectSocket::BoostConnectSocket(boost::asio::io_service& ios)
: _socket(ios), _connected(false)
{

}

BoostConnectSocket::~BoostConnectSocket()
{

}

bool BoostConnectSocket::connect(const std::string &address, unsigned short port)
{
    try
    {
        _socket.connect({boost::asio::ip::address::from_string(address), port});
    }
    catch (boost::system::system_error &e)
    {
        std::cout << "Can't connect to remote, reason: " << e.what() << std::endl;
        return false;
    }
    _connected = true;
    return true;
}

BoostConnectSocket	&BoostConnectSocket::operator<<(const APacket &packet)
{
    boost::system::error_code	ec;
	for (auto it : packet.to_bytes())
	{
		std::cout << (int)it << ":";
	}
	boost::asio::write(_socket, boost::asio::buffer(packet.to_bytes()), ec);
    if (ec)
        _connected = false;
    return *this;
}

BoostConnectSocket	&BoostConnectSocket::operator>>(APacket &packet)
{
    std::vector<uint8_t> buffer(ReadSize);
    boost::system::error_code	ec;

    boost::asio::read(_socket, boost::asio::buffer(buffer, ReadSize), ec);
    if (!ec)
        packet.from_bytes(buffer);
    else
        _connected = false;
    return *this;
}

std::size_t	BoostConnectSocket::write(const std::vector<uint8_t>& data)
{
    boost::system::error_code	ec;
    std::size_t			len;

    len = boost::asio::write(_socket, boost::asio::buffer(data.data(), data.size()), ec);
    if (!ec)
        return len;
    else
    {
        _connected = false;
	std::cerr << "Error write: " << ec.message() << std::endl;
      	return 0;
    }
}

std::size_t	BoostConnectSocket::write(const void* data, size_t size)
{
    boost::system::error_code	ec;
    std::size_t			len;


	len = boost::asio::write(_socket, boost::asio::buffer(data, size), ec);
    if (!ec)
        return len;
    else
    {
        _connected = false;
	std::cerr << "Error write: " << ec.message() << std::endl;
	return 0;
    }
}

std::size_t	BoostConnectSocket::read(std::vector<uint8_t>& buffer, size_t size)
{
    std::vector<uint8_t>	vec;
    boost::system::error_code	ec;

    vec.resize(size);

    std::size_t len = boost::asio::read(_socket, boost::asio::buffer(vec.data(), size), ec);
    buffer.insert(buffer.end(), vec.begin(), vec.end());
    if (!ec)
      return len;
    else
    {
	_connected = false;
	std::cerr << "Error write: " << ec.message() << std::endl;
	return 0;
    }
}

void	BoostConnectSocket::async_write(const std::vector<uint8_t>& data, const t_writeCallback& callback)
{
    auto f = std::bind(&BoostConnectSocket::onWrite, this, callback,
            std::placeholders::_1, std::placeholders::_2);
    boost::asio::async_write(_socket, boost::asio::buffer(data), f);
}

void	BoostConnectSocket::async_read(std::vector<uint8_t>& buffer, size_t size, const t_readCallback& callback)
{
    auto f = std::bind(&BoostConnectSocket::onRead, this,
            callback, std::placeholders::_1, std::placeholders::_2);
    boost::asio::async_read(_socket, boost::asio::buffer(buffer, size), f);
}

void    BoostConnectSocket::async_error(const t_errorCallback& callback)
{
    _errorCall = callback;
}

void	BoostConnectSocket::onAccept()
{

}

bool	BoostConnectSocket::isConnected() const
{
    return _connected;
}

void	BoostConnectSocket::onWrite(const t_writeCallback& callback,
        const boost::system::error_code &ec, size_t size)
{
    if (!ec)
        callback(size);
    else
    {
        _connected = false;
        std::cerr << "Error write: " << ec.message() << std::endl;
        _errorCall();
    }
}

void	BoostConnectSocket::onRead(const t_readCallback& callback,
        const boost::system::error_code &ec, size_t size)
{
    if (!ec)
        callback(size);
    else
    {
        _connected = false;
        std::cerr << "Error read: " << ec.message() << std::endl;
        _errorCall();
    }
}

boost::asio::ip::tcp	BoostConnectSocket::familyFromAddr(const boost::asio::ip::address &addr) const {
    if (addr.is_v4())
        return boost::asio::ip::tcp::v4();
    else if (addr.is_v6())
        return boost::asio::ip::tcp::v6();
    throw std::runtime_error("Family address is not v4 nor v6.");
}
