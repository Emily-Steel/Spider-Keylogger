#include "Spider.hpp"

#include <functional>

#include "AFactory.hpp"

#include "BoostCircularBuffer.hpp"

Spider::Spider(const std::shared_ptr<IConnectSocket>& sock)
:  _handshake_done(false),
   _read(Spider::bufferSize),
  _write(Spider::bufferSize),
  _socket(std::move(sock))
{
    _writeCallback = std::bind(&Spider::onWrite, this, std::placeholders::_1);
    _readCallback = std::bind(&Spider::onRead, this, std::placeholders::_1);
}

void Spider::spy()
{
   read(5);
}

const std::shared_ptr<IConnectSocket>&	Spider::getSocket(void) const
{
  return _socket;
}

void    Spider::read(size_t size)
{
    _socket->async_read(_read, size, _readCallback);
}

void    Spider::write()
{
    _socket->async_write(_write, _writeCallback);
}

bool	Spider::isHandshakeDone(void) const
{
  return _handshake_done;
}

void	Spider::onRead(size_t size)
{
    std::cout << "onRead(" << size << ") " << static_cast<const unsigned char*>(_read.data()) << std::endl;
    std::copy(_write.begin(), _write.end(), _read.begin());

    write();
}

void	Spider::onWrite(size_t size)
{
    std::cout << "onWrite(" << size << ") " << std::endl;

    read(5);
}
