#ifndef _RESULT_HPP_
# define _RESULT_HPP_

# include "APacket.hpp"

class Result: public APacket
{
public:
    Result(PacketType type);
    Result(PacketType type, char success);
    ~Result();

    void print();

protected:
    virtual std::vector<char> to_bytes_body() const;
    virtual void to_readable_body(IReadable &parser) const;
    virtual void from_bytes_body(const std::vector<char> &bytes);
    virtual void from_readable_body(IReadable &parser);
    
private:
    char _success;
};

#endif
