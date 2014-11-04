#ifndef _NETWORK_HPP_
# define _NETWORK_HPP_

#include <map>
#include <string>
#include <memory>

#include "ALog.hpp"
#include "ASocket.hpp"
#include "Spider.hpp"

class Network {
public:
  Network(uint16_t port, const std::string &addr = "0.0.0.0");
  virtual ~Network() = default;
  void		poll_clients(/*std::function<void(const std::string&, APacket&)> callback*/);

  void		broadcast(ASocket::t_bytes &buffer, std::size_t size);

private:
  void		_queueAccept(void);

  void		_onAccept(std::shared_ptr<ASocket> newSock);
  void		_onRead(std::shared_ptr<Spider> spider, ASocket::t_bytes &buffer, std::size_t size);
  void		_onWrite(std::shared_ptr<Spider> spider, std::size_t size);

  std::unique_ptr<ASocket>	_acceptor;
  // contains clients that have gone through handshake
  std::map<std::string, std::shared_ptr<Spider>>	_clients;
  // contains clients that are going through handshake
  std::vector<std::shared_ptr<Spider>>			_pendingClients;
};

#endif
