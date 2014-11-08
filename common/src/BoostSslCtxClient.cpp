#include "BoostSslCtxClient.hpp"

BoostSslCtxClient::BoostSslCtxClient()
  : BoostSslCtx()
{
  _ctx.set_verify_mode(boost::asio::ssl::context::verify_peer);
  _ctx.load_verify_file("certs/server.crt");
}
