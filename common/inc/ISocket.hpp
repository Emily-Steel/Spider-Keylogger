#ifndef _ISOCKET_HPP_
# define _ISOCKET_HPP_

# include <iostream>
# include "APacket.hpp"

# define SIZEREAD 512

class ISocket {

public:
    virtual ~ISocket() {};
    
    virtual bool connect (const std::string &address, int port) = 0;
    virtual ISocket &operator<<(const APacket &packet) = 0;
    virtual ISocket &operator>>(APacket &packet) = 0;
    virtual bool write(void *data, std::size_t size) = 0;
    virtual bool read(std::string &buffer, std::size_t size) = 0;
    
    virtual void bind(int port) = 0;
    virtual void listen(std::size_t backlog) = 0;
    virtual ISocket *accept() = 0;
};

#endif
