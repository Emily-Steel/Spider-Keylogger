#include "KillConfirm.hpp"

KillConfirm::KillConfirm()
: Result(APacket::PacketType::KILLRESPONSE)
{
    
}

KillConfirm::KillConfirm(char success)
: Result(APacket::PacketType::KILLRESPONSE, success)
{
    
}
