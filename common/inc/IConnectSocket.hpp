#ifndef ICONNECT_SOCKET_H
#define ICONNECT_SOCKET_H

#include <string>
#include <vector>
#include <functional>
#include <cstdint>

#include "AFactory.hpp"

#include "APacket.hpp"

class IConnectSocket
{
protected:
    const int ReadSize = 512;

public:
    typedef std::function<void(size_t)> t_writeCallback;
    typedef std::function<void(size_t)> t_readCallback;
    typedef std::function<void()> t_errorCallback;

public:
    virtual ~IConnectSocket() = default;

    virtual IConnectSocket &operator<<(const APacket &packet) = 0;
    virtual IConnectSocket &operator>>(APacket &packet) = 0;
    virtual std::size_t	write(const std::vector<uint8_t> &data) = 0;
    virtual std::size_t	write(const void *data, size_t size) = 0;
    virtual std::size_t	read(std::vector<uint8_t> &buffer, size_t size) = 0;
    virtual void async_write(const std::vector<uint8_t> &data, const t_writeCallback &callback) = 0;
    virtual void async_read(std::vector<uint8_t> &buffer, size_t size, const t_readCallback &callback) = 0;
    virtual void async_error(const t_errorCallback &callback) = 0;

    virtual void onAccept(const std::function<void()>& f = [](){}) = 0;
    virtual bool connect(const std::string &address, unsigned short port) = 0;

    virtual bool isConnected() const = 0;
};

#endif
