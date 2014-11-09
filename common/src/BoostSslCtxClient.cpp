#include "BoostSslCtxClient.hpp"

BoostSslCtxClient::BoostSslCtxClient()
  : BoostSslCtx()
{
  _ctx.set_verify_mode(boost::asio::ssl::context::verify_peer);
  try {
    _ctx.load_verify_file("certs/server.crt");
  } catch (const boost::system::system_error& e) {
    std::cerr << "failed to load client side server certificate: " << e.what() << std::endl;
  }
}
