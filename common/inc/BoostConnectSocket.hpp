#ifndef ABOOST_CONNECT_SOCKET_H
#define ABOOST_CONNECT_SOCKET_H

#include "IConnectSocket.hpp"

#include <boost/asio.hpp>

class BoostConnectSocket : public IConnectSocket
{
public:
    BoostConnectSocket(boost::asio::io_service& ios);
    virtual ~BoostConnectSocket();

    BoostConnectSocket	&operator<<(const APacket& packet) override;
    BoostConnectSocket	&operator>>(APacket& packet) override;
    std::size_t	write(const std::vector<uint8_t>& data) override;
    std::size_t	write(const void* data, size_t size) override;
    std::size_t	read(std::vector<uint8_t>& buffer, size_t size) override;
    void async_write(const std::vector<uint8_t>& data, const t_writeCallback& callback) override;
    void async_read(std::vector<uint8_t>& buffer, size_t size, const t_readCallback& callback) override;
    void async_error(const t_errorCallback& callback) override;

    bool connect(const std::string& address, unsigned short port) override;

    boost::asio::ip::tcp::socket& socket() {return _socket;};

    bool isConnected() const override;

protected:
    void onWrite(const t_writeCallback& callback, const boost::system::error_code &ec, size_t size);
    void onRead(const t_readCallback& callback, const boost::system::error_code &ec, size_t size);

private:
    t_errorCallback _errorCall;
    boost::asio::ip::tcp familyFromAddr(const boost::asio::ip::address& addr) const;

protected:
    boost::asio::ip::tcp::socket _socket;
    bool	_connected;
};

#endif
