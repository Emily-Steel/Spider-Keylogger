#ifndef	BOOSTSSLCTXSERVER_H
# define BOOSTSSLCTXSERVER_H

# include "BoostSslCtx.hpp"

class BoostSslCtxServer : public BoostSslCtx
{
public:
  BoostSslCtxServer();
  virtual ~BoostSslCtxServer() = default;
};

#endif /* BOOSTSSLCTXSERVER_H */
