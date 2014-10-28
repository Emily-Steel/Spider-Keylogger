#include <Server.hpp>
#include "Network.hpp"

Network::Network() {
}

Network::~Network() {
}

void Network::init(int port) {
}

void Network::poll_clients(std::function<void(ALog *, const std::string &, APacket &)> callback) {

}
