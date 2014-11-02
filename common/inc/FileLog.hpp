#ifndef _FILELOG_HPP_
# define _FILELOG_HPP_

# include <fstream>
# include <string>
# include "ALog.hpp"
# include "KeyStroke.hpp"
# include "MouseClick.hpp"

class FileLog: public ALog
{

public:
    FileLog();
    ~FileLog();

    virtual void open(const std::string &path);
    virtual void close();
    virtual bool isGood() const;
    virtual void insert(const APacket &, const std::string &id);
    virtual std::vector<APacket *> dump();

private:
    std::fstream    _fileHandle;
    std::string     _filePath;
};

#endif
