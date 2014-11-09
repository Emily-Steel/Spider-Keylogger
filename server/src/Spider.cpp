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
        std::cout << "zfjzefzpoefzeprfjozpjozfzefefepjofpjoz" << std::endl;
        _network.unregisterSpider(lself);
        std::cout << lself.use_count() << std::endl;
    }, self));


    //do handshake checking here

   read(5);

  // _network.registerSpider(shared_from_this());
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
