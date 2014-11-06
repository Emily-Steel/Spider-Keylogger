#include "BoostFileSystemHelper.hpp"

#include <boost/filesystem.hpp>

AFactoryRegistration<IFileSystemHelper, BoostFileSystemHelper> boostFSHFactRegister("BoostFileSystemHelper");

std::string BoostFileSystemHelper::fileBaseName(const std::string& file)
{
  return boost::filesystem::basename(file);
}

std::string BoostFileSystemHelper::fileExtension(const std::string& file)
{
    return  boost::filesystem::extension(file);
}