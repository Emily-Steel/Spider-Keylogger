#include "Spider.hpp"

#include "AFactory.hpp"
#include "BoostCircularBuffer.hpp"

Spider::Spider()
:  _handshake_done(false),
  _read(new BoostCircularBuffer(Spider::bufferSize)),
  _write(new BoostCircularBuffer(Spider::bufferSize)),
  _socket(nullptr)
{

}

Spider::Spider(const std::shared_ptr<ASocket>& sock)
:  _handshake_done(false),
   _read(new BoostCircularBuffer(Spider::bufferSize)),
  _write(new BoostCircularBuffer(Spider::bufferSize)),
  _socket(sock)
{

}

void	Spider::setSocket(const std::shared_ptr<ASocket>& sock)
{
  _socket.reset(sock.get());
}

const std::shared_ptr<ASocket>&	Spider::getSocket(void) const
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

void	Spider::onRead(const ASocket::t_bytes &buffer)
{
    _read->pushData(buffer);
}

void	Spider::onWrite(std::size_t size)
{
    _write->discardData(size);
}
