#ifndef _NETWORK_HPP_
# define _NETWORK_HPP_

#include <map>
#include <string>
#include <memory>
#include <set>

#include "ALog.hpp"
#include "IListenSocket.hpp"
#include "Spider.hpp"
#include "ISslCtx.hpp"

class Network {
public:
  Network(const std::string &addr, uint16_t port, ALog& log);
  virtual ~Network() = default;

  void		poll_clients();
  void      run();
  void      stop();
  void		broadcast(const std::vector<uint8_t> &buffer);

  void      registerSpider(const std::shared_ptr<Spider>& spider);
  void      unregisterSpider(const std::shared_ptr<Spider>& spider);

private:
  void		queueAccept();

  void		onAccept(const std::shared_ptr<IConnectSocket>& newSock);
  void		onWrite(const std::shared_ptr<Spider>& spider, size_t size);

  ISslCtx	*_ssl;
  std::unique_ptr<IListenSocket>	_acceptor;
  std::set<std::shared_ptr<Spider>>	_clients;
  ALog&     _log;
};

#endif
