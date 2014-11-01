#include "ALog.hpp"

ALog::operator bool() const
{
    return isGood();
}


void ALog::setParser(IReadable *parser)
{
    _parser = parser;
}
