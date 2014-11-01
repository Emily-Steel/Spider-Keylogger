#include "JSONParser.hpp"
#include "FileLog.hpp"

FileLog::FileLog()
: ALog()
{

}

FileLog::~FileLog()
{
    
}

void FileLog::open(const std::string &path)
{
    _fileHandle.open(path.c_str(), std::fstream::out | std::fstream::app);
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

void FileLog::insert(const APacket &packet, const std::string &id)
{
    std::string tmp;

    _parser->clear();
    packet.to_readable(*_parser);
    _parser->put("ID", id);
    _parser->write(tmp);
    _fileHandle << tmp;
}

std::vector<APacket *> FileLog::dump()
{
    std::vector<APacket *>  tab;
    std::string buf;

    return (tab);
}
