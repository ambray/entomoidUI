#include <string>
#include <iostream>
#include <sstream>
#include <windows.h>
#include <memory>
#include "..\src\UiBase.hpp"
#include "..\src\Utils.hpp"
#include "..\src\WinUtils.hpp"

using namespace entomoid;

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrev, LPSTR cmd, int cmdShow)
{

	std::stringstream ss;
	Window<WindowBasic> wb;

	if (!wb.init()) {
		return -1;
	}
	wb.setEventFunc<EventType::QuitEvent>([&](EventObject& ob) { wb.shutdown(); });
	wb.eventLoop();

	return 0;

}