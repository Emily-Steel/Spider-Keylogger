#include <iostream>
#include <vector>
#include <assert.h>

#include "BoostSocket.hpp"

boost::asio::io_service BoostSocket::_service;

BoostSocket::BoostSocket(void) :
  _socket(_service),
  _acceptor(_service)
{

}

bool BoostSocket::connect(const std::string &address, unsigned short port)
{
  assert(_type == Type::NONE);

  try
  {
      boost::asio::ip::address baddr = boost::asio::ip::address::from_string(address);

    _acceptor.open(familyFromAddr(baddr));
    _socket.connect({baddr, port});
    _type = Type::ACTIVE;
    return true;
  }
  catch (boost::system::system_error &e)
  {
    std::cerr << "Cannot connect to the server" << std::endl;
    return false;
  }
}

ASocket& BoostSocket::operator<<(const APacket &packet)
{
  assert(_type == Type::ACTIVE);

  try
  {
    _socket.send(boost::asio::buffer(packet.to_bytes()));
  }
  catch (boost::system::system_error &e)
  {
    _throwNetworkException(e);
  }
  return *this;
}

ASocket& BoostSocket::operator>>(APacket &packet)
{
  assert(_type == Type::ACTIVE);

  try
  {
    std::vector<char> buffer(SIZEREAD);

    _socket.receive(boost::asio::buffer(buffer, SIZEREAD));
    packet.from_bytes(buffer);
  }
  catch (boost::system::system_error &e)
  {
    _throwNetworkException(e);
  }
  return *this;
}

std::size_t BoostSocket::write(void *data, std::size_t size)
{
  assert(_type == Type::ACTIVE);

  try
  {
    return _socket.write_some(boost::asio::buffer(data, size));
  }
  catch (boost::system::system_error &e)
  {
    _throwNetworkException(e);
  }
  return 0;
}

std::size_t BoostSocket::read(std::string &buffer, std::size_t size)
{
  assert(_type == Type::ACTIVE);

  try
  {
    char vec[size];

    std::size_t len = _socket.read_some(boost::asio::buffer(vec, size));
    buffer += vec;
    return len;
  }
  catch (boost::system::system_error &e)
  {
    _throwNetworkException(e);
  }
  return 0;
}

void BoostSocket::bind(const std::string &addr, uint16_t port)
{
  assert(_type == Type::NONE);

  boost::asio::ip::address baddr = boost::asio::ip::address::from_string(addr);

  _acceptor.open(familyFromAddr(baddr));
  _acceptor.bind({baddr, port});
  _type = Type::PASSIVE;
}

void BoostSocket::listen(int backlog)
{
  assert(_type == Type::PASSIVE);

  _acceptor.listen(backlog);
}

std::shared_ptr<ASocket> BoostSocket::accept(void)
{
  assert(_type == Type::PASSIVE);

  auto sock = std::make_shared<BoostSocket>();

  _acceptor.accept(sock->_socket);
  return sock;
}

void BoostSocket::_throwNetworkException(boost::system::system_error &e)
{
  if (e.code() == boost::asio::error::eof)
  {
    std::cerr << "Connection reset by peer." << std::endl;
  }
  throw std::runtime_error("Connection interrupted");
}


boost::asio::ip::tcp BoostSocket::familyFromAddr(const boost::asio::ip::address &addr) const {
    if (addr.is_v4())
        return boost::asio::ip::tcp::v4();
    else if (addr.is_v6())
        return boost::asio::ip::tcp::v6();
    throw std::runtime_error("Family address is not v4 nor v6.");
}
