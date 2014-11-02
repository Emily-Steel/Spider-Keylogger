#include "ALog.hpp"

ALog::ALog()
: _parser(nullptr)
{
    
}

ALog::~ALog()
{
    
}

ALog::operator bool() const
{
    return isGood();
}


void ALog::setParser(IReadable *parser)
{
    _parser = parser;
}
