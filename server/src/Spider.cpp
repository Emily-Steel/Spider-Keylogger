#include "Spider.hpp"

#include <functional>

#include "AFactory.hpp"

#include "BoostCircularBuffer.hpp"

Spider::Spider(const std::shared_ptr<IConnectSocket>& sock)
:  _handshake_done(false),
   _read(new BoostCircularBuffer(Spider::bufferSize)),
  _write(new BoostCircularBuffer(Spider::bufferSize)),
  _socket(sock)
{
    _writeCallback = std::bind(&Spider::onWrite, this, std::placeholders::_1);
    _readCallback = std::bind(&Spider::onRead, this, std::placeholders::_1);
}

const std::shared_ptr<IConnectSocket>&	Spider::getSocket(void) const
{
  return _socket;
}
/*
std::unique_ptr<ICircularBuffer>	&Spider::getReadBuf(void)
{
  return _read;
}

std::unique_ptr<ICircularBuffer>	&Spider::getWriteBuf(void)
{
  return _write;
}*/

void    Spider::read()
{
    _socket->async_read(_buff, 1, _readCallback);
}

void    Spider::write() const
{
    _socket->async_write(_buff2, _writeCallback);
}

bool	Spider::isHandshakeDone(void) const
{
  return _handshake_done;
}

void	Spider::onRead(const std::vector<uint8_t> &buffer)
{
    std::cout << "onRead " << static_cast<const unsigned char*>(buffer.data()) << std::endl;
    _read->pushData(buffer);
}

void	Spider::onWrite(std::size_t size)
{
    std::cout << "onWrite " << size << std::endl;
    _write->discardData(size);
}
