#ifndef _KILLCONFIRM_HPP_
# define _KILLCONFIRM_HPP_

# include "Result.hpp"

class KillConfirm: public Result
{
public:
    KillConfirm();
    KillConfirm(uint8_t success);
};

#endif