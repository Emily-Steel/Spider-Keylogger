#include "SocketFactory.hpp"


SocketFactory SocketFactory::_inst = SocketFactory();

SocketFactory &SocketFactory::getInstance()
{
    return (_inst);
}

ASocket *SocketFactory::createSocket()
{
    return (new BoostSocket());
}
