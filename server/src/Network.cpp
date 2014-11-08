#include "Network.hpp"

#include "AFactory.hpp"

#include "BoostListenSocket.hpp" //ToRemove Factory

Network::Network(uint16_t port, const std::string &addr)
: _acceptor(std::unique_ptr<IListenSocket>(new BoostListenSocket()) /*AFactory<IListenSocket>::instance().create("BoostSocket")*/)
{
  _acceptor->bind(addr, port);
  _acceptor->listen(20);
  _queueAccept();
}

void	Network::poll_clients()
{
    _acceptor->poll();
}

void    Network::run()
{
  _acceptor->start();
}

void    Network::stop()
{
  _acceptor->stop();
}

void	Network::broadcast(const std::vector<uint8_t> &buffer)
{
  for (auto &client : _pendingClients) {
    std::function<void(std::size_t)> w(std::bind(&Network::_onWrite, this, client, std::placeholders::_1));
    client->getSocket()->async_write(buffer, w);
  }
}

void	Network::_queueAccept(void)
{
  std::function<void(std::shared_ptr<IConnectSocket>)> acc(std::bind(&Network::_onAccept, this, std::placeholders::_1));

  _acceptor->async_accept(acc);
}

void	Network::_onAccept(std::shared_ptr<IConnectSocket> newSock)
{
  std::cout << "Accepted a spider." << std::endl;
  _pendingClients.emplace_back(new Spider(newSock));
  _queueAccept();
}

void	Network::_onRead(std::shared_ptr<Spider> spider, std::vector<uint8_t> &buffer, size_t size)
{
  spider->onRead(buffer);
  std::cout << "Some spider said: ";
  for (std::uint8_t b : buffer) {
    std::cout << static_cast<char>(b);
  }
  std::cout << "(" << size << ")" << std::endl;
}

void	Network::_onWrite(std::shared_ptr<Spider> spider, std::size_t size)
{
  (void)spider;
  //spider->onWrite(size);
  std::cout << "Sent a message to a spider (" << size << ")" << std::endl;
}
