#ifndef _AUTOSTART_HPP_
# define _AUTOSTART_HPP_

# include <sys/types.h>
# include <sys/stat.h>
# include <algorithm>
# include <windows.h>
# include <iostream>
# include <fstream>
# include <string>

#include "AFactory.hpp"
#include "IFileSystemHelper.hpp"
#include "BoostFileSystemHelper.hpp"

class AutoStart
{
public:
	AutoStart(const std::string &exeName);
	virtual ~AutoStart();

	void verifyPath() const;
	void verifyRegister() const;

private:
	bool writeInRegister(	const HKEY base_key, const std::string &key_path,
							const std::string &key_name, const std::string &data) const;
	bool copyFile(const std::string &from, const std::string &to) const;
	bool isDirectory(const std::string &path) const;
	bool isFile(const std::string &path) const;
	bool createFile(const std::string &path) const;

	std::string	_name;
};

#endif