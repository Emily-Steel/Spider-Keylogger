#ifndef _NETWORK_HPP_
# define _NETWORK_HPP_

#include <map>
#include <string>
#include <memory>
#include "ASocket.hpp"

class Network {
public:
    Network();
    virtual ~Network() = default;
    void init(uint16_t port);
    void poll_clients (std::function<void(ALog *, const std::string&, APacket&)> callback);

private:
    std::map<std::string, std::unique_ptr<ASocket> > clients;
    std::unique_ptr<ASocket> acceptor;
};

#endif