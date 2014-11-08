#include "Spider.hpp"

#include <functional>

#include "Network.hpp"
#include "AFactory.hpp"

#include "BoostCircularBuffer.hpp"

Spider::Spider(const std::shared_ptr<IConnectSocket>& sock, Network& net)
: _read(Spider::bufferSize),
  _socket(std::move(sock)),
  _network(net)
{
    _write.clear();
    _writeCallback = std::bind(&Spider::onWrite, this, std::placeholders::_1);
    _readCallback = std::bind(&Spider::onRead, this, std::placeholders::_1);
}

void Spider::spy()
{
    _network.registerSpider(shared_from_this());
   read(5);
}

const std::shared_ptr<IConnectSocket>&	Spider::getSocket(void) const
{
  return _socket;
}

Spider& Spider::operator<<(const std::vector<uint8_t>& buff)
{
    _write.insert(_write.end(), buff.begin(), buff.end());
    return *this;
}

void    Spider::read(size_t size)
{
    _socket->async_read(_read, size, _readCallback);
}

void    Spider::write()
{
    _socket->async_write(_write, _writeCallback);
}

void	Spider::onRead(size_t size)
{
    std::cout << "onRead(" << size << ") " << static_cast<const unsigned char*>(_read.data()) << std::endl;

    _write.insert(_write.end(), _read.begin(), _read.begin() + size);
    write();
}

void	Spider::onWrite(size_t size)
{
    _write.clear();
    std::cout << "onWrite(" << size << ") " << std::endl;

    read(5);
}
