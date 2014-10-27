#ifndef _SOCKET_HPP_
# define _SOCKET_HPP_

# include <boost/asio.hpp>
# include "SocketFactory.hpp"
# include "ISocket.hpp"

class BoostSocket : public ISocket
{
public:
    BoostSocket();
    BoostSocket(boost::asio::ip::tcp::socket &socket);
    ~BoostSocket();
    
    virtual bool connect (const std::string &address, int port);
    virtual ISocket &operator<<(const APacket &packet);
    virtual ISocket &operator>>(APacket &packet);
    virtual bool write(void *data, std::size_t size);
    virtual bool read(std::string &buffer, std::size_t size);
    
    virtual void bind(int port);
    virtual void listen(std::size_t backlog);
    virtual ISocket *accept();

private:
    boost::asio::io_service             _io_service;
    boost::asio::ip::tcp::socket        _socket;
    boost::asio::ip::tcp::acceptor      _accept;
};

#endif
