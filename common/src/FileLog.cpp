#include "FileLog.hpp"

FileLog::FileLog()
{
    
}

FileLog::~FileLog()
{
    
}

void FileLog::open(const std::string &path)
{
    _fileHandle.open(path.c_str());
}

void FileLog::close()
{
    if (_fileHandle.is_open())
        _fileHandle.close();
}

bool FileLog::isGood() const
{
    return (_fileHandle.good());
}

ALog &FileLog::operator<<(const APacket &packet)
{
    std::string tmp = packet.to_readable();

    return (*this);
}

ALog &FileLog::operator>>(APacket &packet)
{
    return (*this);
}
