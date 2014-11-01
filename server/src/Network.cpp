#include <Server.hpp>
#include "Network.hpp"

Network::Network() {
}

void Network::init(uint16_t port)
{
}

void Network::poll_clients(std::function<void(ALog *, const std::string &, APacket &)> callback) {

}
