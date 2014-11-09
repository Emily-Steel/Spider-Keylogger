#include "HandshakeResult.hpp"

HandshakeResult::HandshakeResult()
	: Result(APacket::PacketType::SHORTRESPONSE)
{

}

HandshakeResult::HandshakeResult(char success)
	: Result(APacket::PacketType::SHORTRESPONSE, success)
{
    
}
