#include "Network.hpp"

#include "AFactory.hpp"

#include "BoostListenSocket.hpp" //ToRemove Factory

Network::Network(uint16_t port, const std::string &addr)
: _acceptor(std::unique_ptr<IListenSocket>(new BoostListenSocket()) /*AFactory<IListenSocket>::instance().create("BoostSocket")*/)
{
  _acceptor->bind(addr, port);
  _acceptor->listen(20);
  queueAccept();
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

void    Network::registerSpider(const std::shared_ptr<Spider>& spider)
{
    std::cout << "Spider registered with id: " << spider->getIdentity() << std::endl;
    _clients.insert(spider);
}

void      Network::unregisterSpider(const std::shared_ptr<Spider>& spider)
{
    _clients.erase(spider);
}

void	Network::broadcast(const std::vector<uint8_t> &buffer)
{
  for (auto &client : _clients) {
    std::function<void(size_t)> w(std::bind(&Network::onWrite, this, client, std::placeholders::_1));
    client->getSocket()->async_write(buffer, w);
  }
}

void	Network::queueAccept()
{
  std::function<void(std::shared_ptr<IConnectSocket>)> acc(std::bind(&Network::onAccept, this, std::placeholders::_1));

  _acceptor->async_accept(acc);
}

void	Network::onAccept(const std::shared_ptr<IConnectSocket>& newSock)
{
  std::shared_ptr<Spider> spider(new Spider(newSock, *this));
  std::cout << "New client." << std::endl;
  spider->spy();
  queueAccept();
}

void	Network::onWrite(const std::shared_ptr<Spider>& spider, std::size_t size)
{
  (void)spider;
  //spider->onWrite(size);
  std::cout << "Sent a message to a spider (" << size << ")" << std::endl;
}
