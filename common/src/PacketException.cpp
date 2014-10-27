#include "PacketException.hpp"

PacketException::PacketException(const std::string &what)
: std::runtime_error(what)
{
    
}
