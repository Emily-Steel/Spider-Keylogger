#ifndef _REQUEST_HPP_
# define _REQUEST_HPP_

# include "APacket.hpp"

class Request: public APacket
{
public:
    Request(PacketType type);
    ~Request();
    
    void print();

protected:
    virtual std::vector<char> to_bytes_body() const;
    virtual std::string to_readable_body() const;
    virtual void from_bytes_body(const std::vector<char> &);
    virtual void from_readable_body(const std::string &);

};

#endif
