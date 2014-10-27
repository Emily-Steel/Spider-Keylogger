#include "SocketFactory.hpp"


SocketFactory SocketFactory::_inst = SocketFactory();

SocketFactory &SocketFactory::getInstance()
{
    return (_inst);
}

ISocket *SocketFactory::createSocket()
{
    return (new BoostSocket());
}