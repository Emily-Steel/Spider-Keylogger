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

bool	Spider::isHandshakeDone(void) const
{
  return _handshake_done;
}

void	Spider::onRead(const std::vector<uint8_t> &buffer)
{
    _read->pushData(buffer);
}

void	Spider::onWrite(std::size_t size)
{
    _write->discardData(size);
}
