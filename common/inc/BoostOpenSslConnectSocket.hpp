#ifndef ABOOST_OPENSSL_CONNECT_SOCKET_H
#define ABOOST_OPENSSL_CONNECT_SOCKET_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "IConnectSocket.hpp"

#include "BoostSslCtx.hpp"

class BoostOpenSslConnectSocket : public IConnectSocket
{
public:
    BoostOpenSslConnectSocket(boost::asio::io_service& ios, BoostSslCtx& ssl);
    virtual ~BoostOpenSslConnectSocket();

private:
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _sslsocket;
};

#endif
