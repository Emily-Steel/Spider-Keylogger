#include "BoostOpenSslConnectSocket.hpp"

//AFactoryRegistration<IConnectSocket, BoostOpenSslConnectSocket> boostOpenSslSockFactRegister("BoostOpenSslConnectSocket");

BoostOpenSslConnectSocket::BoostOpenSslConnectSocket(boost::asio::io_service &ios, BoostSslCtx &ssl)
  : _sslsocket(ios, ssl.context()), _ios(ios), _connected(false)
{

}

BoostOpenSslConnectSocket::~BoostOpenSslConnectSocket()
{

}

bool BoostOpenSslConnectSocket::connect(const std::string &address, unsigned short port)
{
  try {
    boost::asio::ip::tcp::resolver	resolver(_ios);
    boost::asio::connect(_sslsocket.lowest_layer(), resolver.resolve({address, std::to_string(port)}));
    _sslsocket.handshake(boost::asio::ssl::stream_base::client);
  } catch (boost::system::system_error &e) {
    std::cerr << "Can't connect to remote, reason: " << e.what() << std::endl;
    return false;
  }
  _connected = true;
  return true;
}

BoostOpenSslConnectSocket &BoostOpenSslConnectSocket::operator<<(const APacket &packet)
{
  boost::system::error_code	ec;
  boost::asio::write(_sslsocket, boost::asio::buffer(packet.to_bytes()), ec);
  if (ec)
    _connected = false;
  return *this;
}

BoostOpenSslConnectSocket &BoostOpenSslConnectSocket::operator>>(APacket &packet)
{
  std::vector<uint8_t> buffer(ReadSize);
  boost::system::error_code	ec;

  boost::asio::read(_sslsocket, boost::asio::buffer(buffer, ReadSize), ec);
  if (!ec)
    packet.from_bytes(buffer);
  else
    _connected = false;
  return *this;
}

std::size_t BoostOpenSslConnectSocket::write(const std::vector<uint8_t>&data)
{
  boost::system::error_code	ec;
  std::size_t			len;

  len = boost::asio::write(_sslsocket, boost::asio::buffer(data.data(), data.size()), ec);
  if (!ec)
    return len;
  else
    {
      _connected = false;
      std::cerr << "Error write: " << ec.message() << std::endl;
      return 0;
    }
}

std::size_t BoostOpenSslConnectSocket::write(const void * data, size_t size)
{
  boost::system::error_code	ec;
  std::size_t			len;

  len = boost::asio::write(_sslsocket, boost::asio::buffer(data, size), ec);
  if (!ec)
    return len;
  else
    {
      _connected = false;
      std::cerr << "Error write: " << ec.message() << std::endl;
      return 0;
    }
}

std::size_t BoostOpenSslConnectSocket::read(std::vector<uint8_t>&buffer, size_t size)
{
  std::vector<uint8_t>	vec;
  boost::system::error_code	ec;

  vec.resize(size);

  std::size_t len = boost::asio::read(_sslsocket, boost::asio::buffer(vec.data(), size), ec);
  buffer.insert(buffer.end(), vec.begin(), vec.end());
  if (!ec)
    return len;
  else
    {
      _connected = false;
      std::cerr << "Error write: " << ec.message() << std::endl;
      return 0;
    }
}

void BoostOpenSslConnectSocket::async_write(const std::vector<uint8_t>&data, const t_writeCallback &callback)
{
  auto f = std::bind(&BoostOpenSslConnectSocket::onWrite, this, callback,
		     std::placeholders::_1, std::placeholders::_2);
  boost::asio::async_write(_sslsocket, boost::asio::buffer(data), f);
}

void BoostOpenSslConnectSocket::async_read(std::vector<uint8_t>&buffer, size_t size, const t_readCallback &callback)
{
  auto f = std::bind(&BoostOpenSslConnectSocket::onRead, this,
		     callback, std::placeholders::_1, std::placeholders::_2);
  boost::asio::async_read(_sslsocket, boost::asio::buffer(buffer, size), f);
}

void BoostOpenSslConnectSocket::async_error(const t_errorCallback &callback)
{
  _errorCall = callback;
}

void BoostOpenSslConnectSocket::onAccept()
{
  auto f = std::bind(&BoostOpenSslConnectSocket::onHandshake, this,
		     std::placeholders::_1);
  _sslsocket.async_handshake(boost::asio::ssl::stream_base::server, f);
}

void BoostOpenSslConnectSocket::onHandshake(const boost::system::error_code &ec)
{
  if (ec) {
    _connected = false;
    std::cerr << "Can't connect to remote, reason: " << ec.message() << std::endl;
  }
}

bool BoostOpenSslConnectSocket::isConnected() const
{
  return _connected;
}

void BoostOpenSslConnectSocket::onWrite(const t_writeCallback& callback,
					const boost::system::error_code &ec,
					size_t size)
{
  if (!ec)
    callback(size);
  else
    {
      _connected = false;
      std::cerr << "Error write: " << ec.message() << std::endl;
      _errorCall();
    }
}

void BoostOpenSslConnectSocket::onRead(const t_readCallback& callback,
				       const boost::system::error_code &ec,
				       size_t size)
{
  if (!ec)
    callback(size);
  else
    {
      _connected = false;
      std::cerr << "Error read: " << ec.message() << std::endl;
      _errorCall();
    }
}
