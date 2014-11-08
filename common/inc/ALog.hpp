#ifndef _ILOG_HPP_
# define _ILOG_HPP_

#include <string>

#include "APacket.hpp"
#include "IReadable.hpp"
#include "AFactory.hpp"

class ALog
{
public:

    ALog();
    virtual ~ALog();
    
    virtual void open(const std::string &path) = 0;
    virtual void close() = 0;
    virtual void insert(const APacket &, const std::string &id) = 0;
    virtual std::vector<APacket *> dump() = 0;
    bool isGood() const;
    operator bool() const;

    void    setParser(IReadable *parser);
    
protected:
    IReadable   *_parser;
    bool _good;
};

#endif
