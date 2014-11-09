#include "BoostSslCtx.hpp"

//AFactoryRegistration<IOpenSsl, BoostOpenSsl> boostOpenSslFactRegister("BoostOpenSsl");

BoostSslCtx::BoostSslCtx()
: _ctx(boost::asio::ssl::context::sslv23)
{

}

