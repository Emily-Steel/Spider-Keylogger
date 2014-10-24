#ifndef _HANDSHAKERESULT_HPP_
# define _HANDSHAKERESULT_HPP_

# include "Result.hpp"

class HandShakeResult: public Result
{
public:
    HandShakeResult();
    HandShakeResult(char success);
};

#endif