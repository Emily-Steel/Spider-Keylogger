#include "Network.hpp"

#include "SocketFactory.hpp"

Network::Network(uint16_t port, const std::string &addr)
: _acceptor(SocketFactory::getInstance().createSocket())
{
    _acceptor->bind(addr, port);
}

void Network::poll_clients(std::function<void(const std::string &, APacket &)> callback) {
    (void)callback;
}
