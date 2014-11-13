#include <thread>
#include "BoostOpenSslListenSocket.hpp"

#include "BoostOpenSslConnectSocket.hpp"

BoostOpenSslListenSocket::BoostOpenSslListenSocket(const std::shared_ptr<ISslCtx> &ssl, const std::shared_ptr<boost::asio::io_service>& ios)
  : _ssl(std::dynamic_pointer_cast<BoostSslCtx>(ssl))
  , _ios(ios)
  , _acceptor(*_ios)
{
  if (_ssl.get() == nullptr)
      throw std::runtime_error("BoostOpenSslListenSocket::BoostOpenSslListenSocket context isn't an BoostSslCtx.");
}

BoostOpenSslListenSocket::~BoostOpenSslListenSocket()
{

}

void BoostOpenSslListenSocket::bind(const std::string &addr, uint16_t port)
{
  boost::asio::ip::address baddr = boost::asio::ip::address::from_string(addr);

  _acceptor.open(familyFromAddr(baddr));
  _acceptor.bind({baddr, port});
}

void BoostOpenSslListenSocket::listen(int backlog)
{
  _acceptor.listen(backlog);
}

std::shared_ptr<IConnectSocket>	BoostOpenSslListenSocket::accept()
{
  auto sock = new BoostOpenSslConnectSocket(*_ios, _ssl);

  _acceptor.accept(sock->socket());
  sock->onAccept();
  return std::shared_ptr<IConnectSocket>(sock);
}

void BoostOpenSslListenSocket::async_accept(const t_acceptCallback& callback)
{
  auto sock = new BoostOpenSslConnectSocket(*_ios, _ssl);

  std::function<void(const boost::system::error_code &)> f(std::bind(&BoostOpenSslListenSocket::onAccept, this,
								     callback, std::placeholders::_1,
								     std::shared_ptr<IConnectSocket>(sock)));
  _acceptor.async_accept(sock->socket(), f);
}

void	BoostOpenSslListenSocket::onAccept(const t_acceptCallback& callback,
					   const boost::system::error_code &ec,
					   const std::shared_ptr<IConnectSocket> &sock)
{
  if (!ec) {
      sock->onAccept(std::bind(callback, sock));
  } else {
    std::cerr << "Error onAccept " << ec.message() << std::endl;
  }
  async_accept(callback);
}

void BoostOpenSslListenSocket::poll()
{
  _ios->poll();
}

void BoostOpenSslListenSocket::start()
{
  _ios->run();
}

void BoostOpenSslListenSocket::stop()
{
  _ios->stop();
}

boost::asio::ip::tcp BoostOpenSslListenSocket::familyFromAddr(const boost::asio::ip::address &addr) const {
  if (addr.is_v4())
    return boost::asio::ip::tcp::v4();
  else if (addr.is_v6())
    return boost::asio::ip::tcp::v6();
  throw std::runtime_error("Family address is not v4 nor v6.");
}
