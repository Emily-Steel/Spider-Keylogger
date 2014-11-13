#ifndef	BOOSTOPENSSLLISTENSOCKET_H
# define BOOSTOPENSSLLISTENSOCKET_H

# include <memory>

# include <boost/asio.hpp>

# include "IListenSocket.hpp"
# include "ISslCtx.hpp"
# include "BoostSslCtx.hpp"

class BoostOpenSslListenSocket : public IListenSocket
{
public:
  BoostOpenSslListenSocket(const std::shared_ptr<ISslCtx> &ssl, const std::shared_ptr<boost::asio::io_service>& ios = std::shared_ptr<boost::asio::io_service>(new boost::asio::io_service()));
  virtual ~BoostOpenSslListenSocket();

  void bind(const std::string &addr, uint16_t port) override;
  void listen(int backlog) override;
  std::shared_ptr <IConnectSocket> accept() override;
  void async_accept(const t_acceptCallback &callback) override;

  void poll() override;
  void start() override;
  void stop() override;

  const std::shared_ptr<boost::asio::io_service>& getIoService() const {return _ios;};

protected:
  void onAccept(const t_acceptCallback& callback, const boost::system::error_code &ec, const std::shared_ptr<IConnectSocket>& sock);

private:
  boost::asio::ip::tcp familyFromAddr(const boost::asio::ip::address& addr) const;

protected:
  std::shared_ptr<BoostSslCtx>				_ssl;
  std::shared_ptr<boost::asio::io_service>	_ios;
  boost::asio::ip::tcp::acceptor		_acceptor;
};

#endif /* BOOSTOPENSSLLISTENSOCKET_H */
