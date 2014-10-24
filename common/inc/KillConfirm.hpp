#ifndef _KILLCONFIRM_HPP_
# define _KILLCONFIRM_HPP_

# include "Result.hpp"

class KillConfirm: public Result
{
public:
    KillConfirm();
    KillConfirm(char success);
};

#endif