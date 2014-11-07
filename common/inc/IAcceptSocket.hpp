#ifndef IACCEPT_SOCKET_H
#define IACCEPT_SOCKET_H

#include <string>
#include <vector>
#include <cstdint>

#include "AFactory.hpp"

class IAcceptSocket
{
public:
    virtual ~IAcceptSocket() = default;

    virtual void bind(const std::string &addr, uint16_t port) = 0;
    virtual void listen(int backlog) = 0;
    virtual const std::shared_ptr<ASocket>& accept(void) = 0;
    virtual void async_accept(const std::function<void(const std::shared_ptr<ASocket>&)>& callback) = 0;
};


#endif