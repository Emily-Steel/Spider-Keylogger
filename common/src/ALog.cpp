#include "ALog.hpp"

ALog::ALog()
: _good(false)
{

}

ALog::operator bool() const
{
    return isGood();
}

bool ALog::isGood() const {
    return _good;
}