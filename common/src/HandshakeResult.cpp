#include "HandshakeResult.hpp"

HandshakeResult::HandshakeResult()
: Result(APacket::PacketType::HANDSHAKE)
{

}

HandshakeResult::HandshakeResult(char success)
: Result(APacket::PacketType::HANDSHAKE, success)
{
    
}
