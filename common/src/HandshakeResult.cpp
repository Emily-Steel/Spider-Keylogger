#include "HandshakeResult.hpp"

HandshakeResult::HandshakeResult()
: Result(HANDSHAKE)
{

}

HandshakeResult::HandshakeResult(char success)
: Result(HANDSHAKE, success)
{
    
}
