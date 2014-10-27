#include "BoostSocket.hpp"

BoostSocket::BoostSocket()
: _socket(_io_service), _accept(_io_service)
{

}

BoostSocket::BoostSocket(boost::asio::ip::tcp::socket &socket)
: _socket(_io_service), _accept(_io_service)
{
    _socket.assign(boost::asio::ip::tcp::v4(), socket.native_handle());
}

BoostSocket::~BoostSocket()
{
    
}

bool BoostSocket::connect(const std::string &address, int port)
{
    try
    {
        _socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(address), port));
        return (true);
    }
    catch (boost::system::system_error &e)
    {
        std::cerr << "Cannot connect to the server" << std::endl;
        return (false);
    }
}

ISocket &BoostSocket::operator<<(const APacket &packet)
{
    std::vector<char> vec = packet.to_bytes();
    
    _socket.write_some(boost::asio::buffer(vec));
    return (*this);
}

ISocket &BoostSocket::operator>>(APacket &packet)
{
    return (*this);
}

bool BoostSocket::write(void *data, std::size_t size)
{
    _socket.write_some(boost::asio::buffer(data, size));
    return (true);
}

bool BoostSocket::read(std::string &buffer, std::size_t size)
{
    char data[SIZEREAD + 1] = { 0 };
    
    for (std::size_t i = 0;i < size;i += SIZEREAD)
    {
        _socket.read_some(boost::asio::buffer(data, SIZEREAD));
        buffer += data;
    }
    return (true);
}

void BoostSocket::bind(int port)
{
    _accept.bind(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
}

void BoostSocket::listen(std::size_t backlog)
{
    
}

ISocket *BoostSocket::accept()
{
    boost::asio::ip::tcp::socket    s(_io_service);
    
    _accept.accept(s);
    return (new BoostSocket(s));
}
