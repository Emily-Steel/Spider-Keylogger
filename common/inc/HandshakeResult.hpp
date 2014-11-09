#ifndef _HANDSHAKERESULT_HPP_
# define _HANDSHAKERESULT_HPP_

# include "Result.hpp"

class HandshakeResult: public Result
{
public:
    HandshakeResult();
    HandshakeResult(uint8_t success);
};

#endif