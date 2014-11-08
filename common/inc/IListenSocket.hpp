#ifndef ILISTEN_SOCKET_H
#define ILISTEN_SOCKET_H

#include <string>
#include <memory>

#include "IConnectSocket.hpp"

#include "AFactory.hpp"

class IListenSocket
{
protected:
    typedef std::function<void(const std::shared_ptr<IConnectSocket>&)> t_acceptCallback;

public:
    virtual ~IListenSocket() = default;

    virtual void bind(const std::string &addr, uint16_t port) = 0;
    virtual void listen(int backlog) = 0;
    virtual std::shared_ptr<IConnectSocket> accept() = 0;
    virtual void async_accept(const t_acceptCallback& callback) = 0;

    virtual void poll() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};

#endif
