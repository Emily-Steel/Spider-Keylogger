#include "KillConfirm.hpp"

KillConfirm::KillConfirm()
: Result(APacket::PacketType::KILLRESPONSE)
{
    
}

KillConfirm::KillConfirm(uint8_t success)
: Result(APacket::PacketType::KILLRESPONSE, success)
{
    
}
