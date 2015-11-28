#include <string>
#include <iostream>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#include "../src/WinUtils.hpp"
#endif
#include <memory>
#include "../src/UiBase.hpp"
#include "../src/Utils.hpp"


using namespace entomoid;

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrev, LPSTR cmd, int cmdShow)
#else
int main(int argc, char** argv, char** envp)
#endif
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