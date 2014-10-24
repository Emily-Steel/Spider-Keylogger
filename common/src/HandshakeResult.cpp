#include "HandShakeResult.hpp"

HandShakeResult::HandShakeResult()
: Result(HANDSHAKE)
{
    
}

HandShakeResult::HandShakeResult(char success)
: Result(HANDSHAKE, success)
{
    
}
