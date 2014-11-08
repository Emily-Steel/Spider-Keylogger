#include "BoostSslCtxServer.hpp"

BoostSslCtxServer::BoostSslCtxServer()
  : BoostSslCtx()
{
  _ctx.set_options(boost::asio::ssl::context::default_workarounds
		       | boost::asio::ssl::context::no_sslv2
		       | boost::asio::ssl::context::single_dh_use);
  _ctx.use_certificate_chain_file("certs/server.crt");
  _ctx.use_private_key_file("certs/server.key", boost::asio::ssl::context::pem);
  _ctx.use_tmp_dh_file("certs/dh512.pem");
}

