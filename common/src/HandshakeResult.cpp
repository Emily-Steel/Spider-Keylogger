#include "HandshakeResult.hpp"

HandshakeResult::HandshakeResult()
	: Result(APacket::PacketType::SHORTRESPONSE)
{

}

HandshakeResult::HandshakeResult(uint8_t success)
: Result(APacket::PacketType::SHORTRESPONSE, success)
{
    
}
