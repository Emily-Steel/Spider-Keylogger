#include "FileLog.hpp"

FileLog::FileLog()
{
    
}

FileLog::~FileLog()
{
    
}

void FileLog::open(const std::string &path)
{
    _fileHandle.open(path.c_str(), std::fstream::out | std::fstream::app);
    if (_fileHandle.is_open())
        _good = true;
}

void FileLog::close()
{
    if (_fileHandle.is_open())
        _fileHandle.close();
    _good = false;
}

void FileLog::insert(const APacket &packet, const std::string &id)
{
    (void)packet;
    (void)id;
//    std::string tmp = packet.to_readable();

//    return (*this);
}

std::vector<APacket *> FileLog::dump()
{
//    return (*this);
}
