#include "HandshakeResult.hpp"

HandshakeResult::HandshakeResult()
: Result(APacket::PacketType::HANDSHAKE)
{

}

HandshakeResult::HandshakeResult(uint8_t success)
: Result(APacket::PacketType::HANDSHAKE, success)
{
    
}
