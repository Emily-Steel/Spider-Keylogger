#ifndef ABOOST_OSSL_SOCK_H
#define ABOOST_OSSL_SOCK_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "IConnectSocket.hpp"

#include "BoostOpenSsl.hpp"

class BoostOpenSslSocket : public IConnectSocket
{
public:
    BoostOpenSslSocket(boost::asio::io_service& ios, BoostOpenSsl& ssl);
    virtual ~BoostOpenSslSocket();

private:
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _sslsocket;
};

#endif