#include "BoostOpenSslSocket.hpp"

//AFactoryRegistration<IConnectSocket, BoostOpenSslSocket> boostOpenSslSockFactRegister("BoostOpenSslSocket");

BoostOpenSslSocket::BoostOpenSslSocket(boost::asio::io_service& ios, BoostOpenSsl& ssl)
: _sslsocket(ios, ssl.context())
{

}

BoostOpenSslSocket::~BoostOpenSslSocket()
{

}