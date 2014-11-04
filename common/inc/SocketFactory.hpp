#ifndef _SOCKETFACTORY_hpp
# define _SOCKETFACTORY_hpp

#include <memory>

# include "ASocket.hpp"
# include "BoostSocket.hpp"

class SocketFactory {
    
public:
    static SocketFactory &getInstance();
    ASocket *createSocket();
    
private:
    SocketFactory() { }
    ~SocketFactory() { }
    
    SocketFactory &operator=(const SocketFactory &) = delete;
    SocketFactory(const SocketFactory &) { }
    
    static SocketFactory _inst;
};

#endif
