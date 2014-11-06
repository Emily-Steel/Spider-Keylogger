#ifndef	_BOOSTSOCKET_HPP_
# define _BOOSTSOCKET_HPP_

# include <string>
# include <boost/asio.hpp>

# include "ASocket.hpp"

class BoostSocket : public ASocket
{
public:
  static boost::asio::io_service	_service;

  BoostSocket(void);
  virtual ~BoostSocket(void) = default;
  BoostSocket(const BoostSocket&other) = delete;
  BoostSocket	&operator=(const BoostSocket&other) = delete;

  ASocket	&operator<<(const APacket &packet) override;
  ASocket	&operator>>(APacket &packet) override;
  std::size_t	write(void *data, std::size_t size) override;
  std::size_t	read(t_bytes &buffer, std::size_t size) override;
  void		async_write(void *data, std::size_t size, t_writeCallback callback) override;
  void		async_read(t_bytes &buffer, std::size_t size, t_readCallback callback) override;

  bool				connect(const std::string &address, unsigned short port) override;
  void				bind(const std::string &addr, uint16_t port) override;
  void				listen(int backlog) override;
  std::shared_ptr<ASocket>	accept(void) override;
  void				async_accept(t_acceptCallback callback) override;

private:
  void		_onAccept(t_acceptCallback callback, const boost::system::error_code &ec, std::shared_ptr<ASocket> sock);
  void		_onRead(t_readCallback callback, const boost::system::error_code &ec, t_bytes& buffer, std::size_t size);
  void		_onWrite(t_writeCallback callback, const boost::system::error_code &ec, std::size_t size);
  boost::asio::ip::tcp familyFromAddr(const boost::asio::ip::address& addr) const;

  // only used if the socket is an active one
  boost::asio::ip::tcp::socket		_socket;
  // only used if the socket is a passive one
  boost::asio::ip::tcp::acceptor	_acceptor;
};

#endif /* BOOSTSOCKET_H */
