#include "Spider.hpp"

Spider::Spider() :
  _handshake_done(false),
  _read(Spider::bufferSize),
  _write(Spider::bufferSize),
  _socket(nullptr)
{

}

Spider::Spider(std::shared_ptr<ASocket> sock) :
  _handshake_done(false),
  _read(Spider::bufferSize),
  _write(Spider::bufferSize),
  _socket(sock)
{

}

void	Spider::setSocket(std::shared_ptr<ASocket> sock)
{
  _socket.reset(sock.get());
}

std::shared_ptr<ASocket>	Spider::getSocket(void) const
{
  return _socket;
}

boost::circular_buffer<std::uint8_t>	&Spider::getReadBuf(void)
{
  return _read;
}

boost::circular_buffer<std::uint8_t>	&Spider::getWriteBuf(void)
{
  return _write;
}

bool	Spider::isHandshakeDone(void) const
{
  return _handshake_done;
}

void	Spider::onRead(ASocket::t_bytes &buffer, std::size_t size)
{
  for (std::size_t i = 0; i < size; ++i) {
    _read.push_back(buffer[i]);
  }
}

void	Spider::onWrite(std::size_t size)
{
  for (unsigned long i = 0; i < size; ++i) {
    _write.pop_front();
  }
}
