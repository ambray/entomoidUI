#include <string>
#include <iostream>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#include "../src/win/WinUtils.hpp"
#elif __linux__
#include "../src/nix/LinUtils.hpp"
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
		ss << "Failed to initialize!" << std::endl;
		std::cerr << ss.str();
		return -1;
	}

	wb.setEventFunc<EventType::QuitEvent>([&](EventObject& ob) { wb.shutdown(); });
	wb.eventLoop();

	return 0;

}