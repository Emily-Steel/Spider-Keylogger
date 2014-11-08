#ifndef _NETWORK_HPP_
# define _NETWORK_HPP_

#include <map>
#include <string>
#include <memory>

#include "ALog.hpp"
#include "IListenSocket.hpp"
#include "Spider.hpp"

class Network {
public:
  Network(uint16_t port, const std::string &addr = "0.0.0.0");
  virtual ~Network() = default;

  void		poll_clients();
  void      run();
  void      stop();
  void		broadcast(const std::vector<uint8_t> &buffer);

private:
  void		_queueAccept(void);

  void		_onAccept(std::shared_ptr<IConnectSocket> newSock);
  void		_onRead(std::shared_ptr<Spider> spider, std::vector<uint8_t> &buffer, size_t size);
  void		_onWrite(std::shared_ptr<Spider> spider, size_t size);

  std::unique_ptr<IListenSocket>	_acceptor;
  // contains clients that have gone through handshake
  std::map<std::string, std::shared_ptr<Spider>>	_clients;
  // contains clients that are going through handshake
  std::vector<std::shared_ptr<Spider>>			_pendingClients;
};

#endif
