#include "Network.hpp"

#include "SocketFactory.hpp"

Network::Network(uint16_t port, const std::string &addr)
: _acceptor(SocketFactory::getInstance().createSocket())
{
  _acceptor->bind(addr, port);
  _acceptor->listen(20);
  _queueAccept();
}

void	Network::poll_clients(/*std::function<void(const std::string &, APacket &)> callback*/)
{
  BoostSocket::_service.poll();
}

void	Network::broadcast(ASocket::t_bytes &buffer, std::size_t size)
{
  std::function<void(std::size_t)> w(std::bind(&Network::_onWrite, this, std::placeholders::_1));

  for (auto &client : _pendingClients) {
    // client->write(buffer.data(), size);
    client->async_write(buffer.data(), size, w);
  }
}

void	Network::_queueAccept(void)
{
  std::function<void(std::shared_ptr<ASocket>)> acc(std::bind(&Network::_onAccept, this, std::placeholders::_1));

  _acceptor->async_accept(acc);
}

void	Network::_onAccept(std::shared_ptr<ASocket> newSock)
{
  std::cout << "Accepted a bitch." << std::endl;
  _pendingClients.push_back(newSock);
  _queueAccept();
}

void	Network::_onRead(ASocket::t_bytes &buffer, std::size_t size)
{
  std::cout << "Some bitch said: ";
  for (std::uint8_t b : buffer) {
    std::cout << static_cast<char>(b);
  }
  std::cout << "(" << size << ")" << std::endl;
}

void	Network::_onWrite(std::size_t size)
{
  std::cout << "Told that bitch off (" << size << ")" << std::endl;
}
