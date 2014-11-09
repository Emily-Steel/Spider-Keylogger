#include "ALog.hpp"

ALog::ALog()
: _parser(nullptr), _good(false)
{
    
}

ALog::~ALog()
{
}

ALog::operator bool() const
{
    return isGood();
}


void ALog::setParser(const std::shared_ptr<IReadable>& parser)
{
    _parser = parser;
}

bool ALog::isGood() const {
    return _good;
}
