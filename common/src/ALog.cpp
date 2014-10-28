#include "ALog.hpp"

ALog::operator bool() const
{
    return isGood();
}