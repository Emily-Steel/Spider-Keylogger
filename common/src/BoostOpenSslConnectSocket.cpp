#include "BoostOpenSslConnectSocket.hpp"

//AFactoryRegistration<IConnectSocket, BoostOpenSslConnectSocket> boostOpenSslSockFactRegister("BoostOpenSslConnectSocket");

BoostOpenSslConnectSocket::BoostOpenSslConnectSocket(boost::asio::io_service& ios, BoostSslCtx& ssl)
: _sslsocket(ios, ssl.context())
{

}

BoostOpenSslConnectSocket::~BoostOpenSslConnectSocket()
{

}
