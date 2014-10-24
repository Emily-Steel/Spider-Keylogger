#ifndef _SOCKET_HPP_
# define _SOCKET_HPP_

#include "ISocket.hpp"

class BoostSocket : public ISocket
{
public:
    BoostSocket();
    ~BoostSocket();
    
    virtual bool connect (std::string address, int port);
    virtual ISocket &operator<<(const APacket &packet);
    virtual ISocket &operator>>(APacket &packet);
    virtual bool write(void *data, std::size_t size);
    virtual bool read(const std::string buffer, std::size_t size);
    
    virtual void bind(int port);
    virtual void listen(std::size_t backlog);
    virtual ISocket *accept();

private:
    
};

#endif
