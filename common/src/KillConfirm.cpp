#include "KillConfirm.hpp"

KillConfirm::KillConfirm()
: Result(KILLRESPONSE)
{
    
}

KillConfirm::KillConfirm(char success)
: Result(KILLRESPONSE, success)
{
    
}
