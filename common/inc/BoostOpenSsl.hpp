#ifndef ABOOST_OPEN_SSL_H
#define ABOOST_OPEN_SSL_H

#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "IOpenSsl.hpp"


class BoostOpenSsl : public IOpenSsl
{
public:
    BoostOpenSsl();
    virtual ~BoostOpenSsl() = default;

    bool verifyCertificate() const;

    boost::asio::ssl::context& context() {return _ctx;};

private:
    boost::asio::ssl::context _ctx;

};

#endif