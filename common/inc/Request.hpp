#ifndef _REQUEST_HPP_
# define _REQUEST_HPP_

# include "APacket.hpp"

class Request: public APacket
{
public:
    Request(PacketType type);
    ~Request();
    
    virtual std::vector<char> to_bytes();
    virtual std::string to_readable();
    virtual void from_bytes(const std::vector<char> &bytes);
    virtual void from_readable(const std::string &data);
    
    void print();
};

#endif
