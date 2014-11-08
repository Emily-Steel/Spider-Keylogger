#include "BoostConnectSocket.hpp"

//AFactoryRegistration<IConnectSocket, BoostConnectSocket> boostConnectSocketFactReg("BoostConnectSocket");

BoostConnectSocket::BoostConnectSocket(boost::asio::io_service& ios)
: _socket(ios)
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
    return true;
}

BoostConnectSocket	&BoostConnectSocket::operator<<(const APacket &packet)
{
    _socket.send(boost::asio::buffer(packet.to_bytes()));
    return *this;
}

BoostConnectSocket	&BoostConnectSocket::operator>>(APacket &packet)
{
    std::vector<char> buffer(ReadSize);

    _socket.receive(boost::asio::buffer(buffer, ReadSize));
    packet.from_bytes(buffer);
    return *this;
}

std::size_t	BoostConnectSocket::write(const std::vector<uint8_t>& data)
{
    return _socket.write_some(boost::asio::buffer(data.data(), data.size()));
}

std::size_t	BoostConnectSocket::write(const void* data, size_t size)
{
    return _socket.write_some(boost::asio::buffer(data, size));
}

std::size_t	BoostConnectSocket::read(std::vector<uint8_t>& buffer, size_t size)
{
    std::vector<uint8_t>	vec;

    vec.resize(size);
    std::size_t len = _socket.read_some(boost::asio::buffer(vec.data(), size));
    buffer.insert(buffer.end(), vec.begin(), vec.end());
    return len;
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

void	BoostConnectSocket::onWrite(const t_writeCallback& callback,
        const boost::system::error_code &ec,
        size_t size)
{
    if (!ec)
        callback(size);
    else
        std::cerr << "Error write: " << ec.message() << std::endl;
}

void	BoostConnectSocket::onRead(const t_readCallback& callback,
        const boost::system::error_code &ec, size_t size)
{
    if (!ec)
        callback(size);
    else
        std::cerr << "Error read: " << ec.message() << std::endl;
}

boost::asio::ip::tcp	BoostConnectSocket::familyFromAddr(const boost::asio::ip::address &addr) const {
    if (addr.is_v4())
        return boost::asio::ip::tcp::v4();
    else if (addr.is_v6())
        return boost::asio::ip::tcp::v6();
    throw std::runtime_error("Family address is not v4 nor v6.");
}
