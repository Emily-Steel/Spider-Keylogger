#ifndef _ILOG_HPP_
# define _ILOG_HPP_

# include <string>
# include "APacket.hpp"

class ALog
{
public:
    virtual ~ALog() {};
    
    virtual void open(const std::string &path) = 0;
    virtual void close() = 0;
    virtual bool isGood() const = 0;
    virtual ALog &operator<<(const APacket &) = 0;
    virtual ALog &operator>>(APacket &) = 0;
    
    operator bool() const;
};

#endif
