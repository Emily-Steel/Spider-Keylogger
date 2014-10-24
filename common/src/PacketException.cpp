#include "PacketException.hpp"

PacketException::PacketException(const std::string &what)
: runtime_error(what)
{
    
}
