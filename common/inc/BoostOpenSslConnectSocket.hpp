#ifndef ABOOST_OPENSSL_CONNECT_SOCKET_H
#define ABOOST_OPENSSL_CONNECT_SOCKET_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "IConnectSocket.hpp"

#include "BoostSslCtx.hpp"

class BoostOpenSslConnectSocket : public IConnectSocket
{
public:
  typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket>	ssl_socket;

  BoostOpenSslConnectSocket(boost::asio::io_service &ios, BoostSslCtx &ssl);
  virtual ~BoostOpenSslConnectSocket();

  virtual BoostOpenSslConnectSocket &operator<<(const APacket &packet) override;
  virtual BoostOpenSslConnectSocket &operator>>(APacket &packet) override;
  virtual std::size_t	write(const std::vector<uint8_t> &data) override;
  virtual std::size_t	write(const void *data, size_t size) override;
  virtual std::size_t	read(std::vector<uint8_t> &buffer, size_t size) override;
  virtual void async_write(const std::vector<uint8_t> &data, const t_writeCallback &callback) override;
  virtual void async_read(std::vector<uint8_t> &buffer, size_t size, const t_readCallback &callback) override;
  virtual void async_error(const t_errorCallback &callback) override;

  ssl_socket::lowest_layer_type& socket() {return _sslsocket.lowest_layer();};

  virtual void onAccept() override;
  virtual bool connect(const std::string &address, unsigned short port) override;

  virtual bool isConnected() const override;

private:
  void onWrite(const t_writeCallback& callback, const boost::system::error_code &ec, size_t size);
  void onRead(const t_readCallback& callback, const boost::system::error_code &ec, size_t size);
  void onHandshake(const boost::system::error_code &ec);

  ssl_socket _sslsocket;
  boost::asio::io_service	&_ios;
  t_errorCallback _errorCall;
  bool _connected;
};

#endif
