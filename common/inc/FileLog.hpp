#ifndef _FILELOG_HPP_
# define _FILELOG_HPP_

# include <fstream>
# include "ALog.hpp"

class FileLog: public ALog
{

public:
    FileLog();
    ~FileLog();

    virtual void open(const std::string &path);
    virtual void close();
    virtual bool isGood() const;
    virtual void insert(const APacket &, const std::string &id) = 0;
    virtual std::vector<APacket *> dump() = 0;

private:
    std::fstream    _fileHandle;
};

#endif