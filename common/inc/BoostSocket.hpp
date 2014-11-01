#ifndef	BOOSTSSLSOCKET_H
# define BOOSTSSLSOCKET_H

# include <string>
# include	<boost/asio.hpp>

# include "ASocket.hpp"

class BoostSocket : public ASocket
{
public:
  BoostSocket(void);
  virtual ~BoostSocket(void) = default;
  BoostSocket(const BoostSocket&other) = delete;
  BoostSocket&operator=(const BoostSocket&other) = delete;

  bool				connect(const std::string &address, unsigned short port) override;
  ASocket&          operator<<(const APacket &packet) override;
  ASocket           &operator>>(APacket &packet) override;
  std::size_t write(void *data, std::size_t size) override;
  std::size_t read(std::string &buffer, std::size_t size) override;

  void				bind(unsigned short port) override;
  void				listen(int backlog) override;
  std::shared_ptr<ASocket>	accept(void) override;

private:
  void        _throwNetworkException(boost::system::system_error &e);

  static boost::asio::io_service    _service;

  // only used if the socket is an active one
  boost::asio::ip::tcp::socket			_socket;
  // only used if the socket is a passive one
  boost::asio::ip::tcp::acceptor		_acceptor;
};

#endif /* BOOSTSSLSOCKET_H */
