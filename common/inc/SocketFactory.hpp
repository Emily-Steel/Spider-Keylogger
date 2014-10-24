#ifndef _SOCKETFACTORY_hpp
# define _SOCKETFACTORY_hpp

# include "ISocket.hpp"
# include "BoostSocket.hpp"

class SocketFactory {
    
public:
    SocketFactory();
    ~SocketFactory();
    
    ISocket *createSocket();
};

#endif
