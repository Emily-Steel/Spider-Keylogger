#ifndef ABOOST_SSLCTX_H
#define ABOOST_SSLCTX_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "ISslCtx.hpp"

class BoostSslCtx : public ISslCtx
{
public:
    BoostSslCtx();
    virtual ~BoostSslCtx() = default;

    boost::asio::ssl::context& context() {return _ctx;};

protected:
    boost::asio::ssl::context _ctx;
};

#endif
