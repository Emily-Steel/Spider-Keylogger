#include "BoostOpenSsl.hpp"

//AFactoryRegistration<IOpenSsl, BoostOpenSsl> boostOpenSslFactRegister("BoostOpenSsl");

BoostOpenSsl::BoostOpenSsl()
: _ctx(boost::asio::ssl::context::sslv23)
{

}

