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
    virtual std::vector<uint8_t> to_bytes_body() const;
    virtual void to_readable_body(IReadable &parser) const;
    virtual void from_bytes_body(const std::vector<uint8_t> &);
    virtual void from_readable_body(IReadable &parser);

};

#endif
