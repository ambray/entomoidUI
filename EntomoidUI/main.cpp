#include <string>
#include <iostream>
#include <windows.h>
#include <memory>
#include "UiBase.hpp"
#include "Utils.hpp"
#include "WinUtils.hpp"

using namespace entomoid;
class BaseTest {
public:
	virtual void test() = 0;
	virtual ~BaseTest() {}
};
HWND hwin;
LRESULT CALLBACK WndFunc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

class TestClass : public virtual BaseTest {
private:
	std::shared_ptr<void> cb_;
	std::string testString;
public:
	virtual void test() override
	{

	}

	virtual DWORD cb(PVOID f, int a, int b, int c)
	{
		std::cout << "Derp " << " " << (int)f << " " << a << " " << b << " " << c << " " << testString << std::endl;
		return 10;
	}

	void init()
	{
		auto fpt = &TestClass::cb;
		testString = "asdfasdf";
		std::cout << "Init: " << std::hex << " 0x" << (size_t&)fpt << std::endl;
		cb_ = entomoid::utils::makeClosure(this, fpt);
	}


	auto getCb()
	{
		return cb_;
	}
};

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hPrev, LPSTR cmd, int cmdShow)
{
	Window<WindowBasic> wb;
	if (!wb.init(hinst)) {
		return -1;
	}
	MSG msg = { 0 };
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}