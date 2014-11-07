#include <iostream>
#include "FileLog.hpp"

FileLog::FileLog()
: ALog()
{

}

FileLog::~FileLog()
{
    close();
}

void FileLog::open(const std::string &path)
{
    _filePath = path;
    _fileHandle.open(path.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
    if (_fileHandle.is_open())
        _good = true;
}

void FileLog::close()
{
    _filePath.clear();
    if (_fileHandle.is_open())
        _fileHandle.close();
    _good = false;
}

void FileLog::insert(const APacket &packet, const std::string &id)
{
    if (!_parser)
        return ;
    
    std::string tmp;

    _parser->clear();
    packet.to_readable(*_parser);
    _parser->put("ID", id);
    _parser->write(tmp);
    _fileHandle << tmp;
}

std::vector<APacket *>  FileLog::dump()
{
    KeyStroke   _key;
    MouseClick  _mouse;

    std::vector<APacket *>  tab;
    std::string buf;
    std::string tmp;

    if (!isGood() || !_parser)
        throw std::invalid_argument("Error while dumping the file");
    
    _fileHandle.seekg(std::ios_base::beg);
    while (std::getline(_fileHandle, tmp))
        buf += tmp;
    
    while (!buf.empty() && buf != "\n")
    {
        tmp = buf;
        try
        {
            _key.from_readable(tmp, *_parser);
            tab.push_back(new KeyStroke(_key));
            buf = tmp;
        }
        catch (std::invalid_argument &e)
        {
            _mouse.from_readable(buf, *_parser);
            tab.push_back(new MouseClick(_mouse));
        }
    }

    _fileHandle.close();
    _fileHandle.open(_filePath.c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);
    return (tab);
}
