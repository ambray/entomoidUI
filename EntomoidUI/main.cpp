#include <string>
#include <iostream>
#include <windows.h>
#include <memory>
#include "UiBase.hpp"
#include "Utils.hpp"
#include "WinUtils.hpp"

using namespace entomoid;

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrev, LPSTR cmd, int cmdShow)
{
	Window<WindowBasic> wb;
	if (!wb.init()) {
		return -1;
	}

	wb.eventLoop();


	return 0;

}