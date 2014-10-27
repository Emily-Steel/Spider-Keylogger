#ifndef _PACKETEXCEPTION_HPP_
# define _PACKETEXCEPTION_HPP_

# include <stdexcept>
# include <string>

class PacketException: public std::runtime_error
{
public:
    PacketException(const std::string &what);
};

#endif
