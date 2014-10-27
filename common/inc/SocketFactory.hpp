#ifndef _SOCKETFACTORY_hpp
# define _SOCKETFACTORY_hpp

# include "ISocket.hpp"
# include "BoostSocket.hpp"

class SocketFactory {
    
public:
    static SocketFactory &getInstance();
    ISocket *createSocket();
    
private:
    SocketFactory() { }
    ~SocketFactory() { }
    
    SocketFactory &operator=(const SocketFactory &) { }
    SocketFactory(const SocketFactory &) { }
    
    static SocketFactory _inst;
};

#endif
