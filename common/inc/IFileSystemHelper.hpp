#ifndef IFILE_SYSTEM_HELPER_H
#define IFILE_SYSTEM_HELPER_H

#include <string>

#include "AFactory.hpp"

class IFileSystemHelper
{
public:
    virtual ~IFileSystemHelper() = default;

    virtual std::string fileBaseName(const std::string& file) = 0;
    virtual std::string fileExtension(const std::string& file) = 0;
};

#endif