#ifndef _NETWORK_HPP_
# define _NETWORK_HPP_

#include <map>
#include <string>
#include <memory>

#include "ALog.hpp"
#include "ASocket.hpp"

class Network {
public:
    Network(uint16_t port, const std::string &addr = "0.0.0.0");
    virtual ~Network() = default;
    void poll_clients(std::function<void(const std::string&, APacket&)> callback);

private:
    std::map<std::string, std::unique_ptr<ASocket> > _clients;
    std::unique_ptr<ASocket> _acceptor;
};

#endif