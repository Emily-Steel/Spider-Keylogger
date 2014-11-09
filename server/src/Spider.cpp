#include "Spider.hpp"

#include <functional>

#include "Network.hpp"
#include "AFactory.hpp"

#include "BoostCircularBuffer.hpp"

Spider::Spider(const std::shared_ptr<IConnectSocket>& sock, Network& net)
: _identified(false),
  _protoVersion(0),
  _read(Spider::bufferSize),
  _socket(std::move(sock)),
  _network(net)
{
    _write.clear();
}

Spider::~Spider()
{
    std::cout << "Bye spider" << std::endl;
}

void Spider::spy()
{
    auto self(shared_from_this());
    _socket->async_error(std::bind([this](std::shared_ptr<Spider> lself)
    {
        _network.unregisterSpider(lself);
        std::cout << lself.use_count() << std::endl;
    }, self));

    _socket->async_read(_read, 4, [this, self](size_t csize){doHandshake(csize);});
}

const std::shared_ptr<IConnectSocket>&	Spider::getSocket(void) const
{
  return _socket;
}

void Spider::doHandshake(size_t size)
{
  auto self(shared_from_this());
  if ((_protoVersion == 0) && (size == 4))
  {
      _protoVersion = *(reinterpret_cast<uint32_t*>(_read.data()));
      std::cout << "Client Proto Version: " << _protoVersion << std::endl;
      if (_protoVersion == 0x312E3076) {
          _socket->async_read(_read, 1, [this, self](size_t csize){doHandshake(csize);});
      }
  }
  else if (size == 1)
  {
      char tmp[2];
      tmp[0] = _read[0];
      tmp[1] = '\0';
      if (_read[0] != '\0') {
          _identity += tmp;
          _socket->async_read(_read, 1, [this, self](size_t csize){doHandshake(csize);});
      }
      else {
          _network.registerSpider(self);
          _socket->async_write(_write, [this, self](size_t csize){onWrite(csize);});
          _socket->async_read(_read, 1, [this, self](size_t csize){onRead(csize);});
      }
  }
}

Spider& Spider::operator<<(const std::vector<uint8_t>& buff)
{
    _write.insert(_write.end(), buff.begin(), buff.end());
    return *this;
}

void    Spider::read(size_t size)
{
    auto self(shared_from_this());
    _socket->async_read(_read, size, [this, self](size_t csize)
    {
        onRead(csize);
    });
}

void    Spider::write()
{
    auto self(shared_from_this());
    _socket->async_write(_read, [this, self](size_t csize)
    {
        onWrite(csize);
    });
}

void	Spider::onRead(size_t size)
{

/*    std::cout << "onRead(" << size << ") " << static_cast<const unsigned char*>(_read.data()) << std::endl;

    _write.insert(_write.end(), _read.begin(), _read.begin() + size);
    write();*/
}

void	Spider::onWrite(size_t size)
{
    _write.clear();
    std::cout << "onWrite(" << size << ") " << std::endl;

    read(5);
}
