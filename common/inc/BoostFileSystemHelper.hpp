#ifndef BOOST_FILE_SYSTEM_HELPER_H
#define BOOST_FILE_SYSTEM_HELPER_H

#include "IFileSystemHelper.hpp"

class BoostFileSystemHelper : public IFileSystemHelper
{
public:
    BoostFileSystemHelper() = default;
    virtual ~BoostFileSystemHelper() = default;

    std::string fileBaseName(const std::string& file) override;
    std::string fileExtension(const std::string& file) override;
};

#endif