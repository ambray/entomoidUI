#include "WinUi.hpp"

LRESULT entomoid::WindowBase::WndFunc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg) {
	case WM_KEYDOWN:
		if (wparam == VK_ESCAPE) 
			shutdown();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

bool entomoid::WindowBase::init()
{
	WNDCLASSEXA wc = { 0 };
	std::string className = "test";

	try {
		callback_ = utils::makeClosure(this, &WindowBase::WndFunc);

		wc.cbSize = sizeof(wc);
		wc.style = 0;
		wc.lpfnWndProc = reinterpret_cast<WNDPROC>(callback_.get());
		wc.hInstance = GetModuleHandle(nullptr);
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 2);
		wc.lpszClassName = className.c_str();

		if (!RegisterClassEx(&wc)) {
			WRAP_WINDOWS_RUNTIME_ERROR("Unable to register class!");
		}

		if (nullptr == (window_ = CreateWindowEx(0, className.c_str(), "Title.", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), nullptr))) {
			WRAP_WINDOWS_RUNTIME_ERROR("Failed to create Window!");
		}

		ShowWindow(window_, SW_SHOW);
		UpdateWindow(window_);

	}
	catch (const std::runtime_error& e) {
		std::cout << "Runtime error! " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Exception! " << e.what() << std::endl;
		return false;
	}

	active_ = true;
	return true;
}

void entomoid::WindowBase::shutdown()
{
	if (active_)
		DestroyWindow(window_);
}
