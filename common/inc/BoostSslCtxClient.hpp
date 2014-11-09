#ifndef	BOOSTSSLCTXCLIENT_H
# define BOOSTSSLCTXCLIENT_H

# include "BoostSslCtx.hpp"

class BoostSslCtxClient : public BoostSslCtx
{
public:
  BoostSslCtxClient();
  virtual ~BoostSslCtxClient() = default;
};

#endif /* BOOSTSSLCTXCLIENT_H */
