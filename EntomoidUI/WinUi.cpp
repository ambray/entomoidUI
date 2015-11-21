#include "WinUi.hpp"
/********************************************************************************
* The MIT License (MIT)
*
* Copyright (c) 2015, Aaron M. Bray, aaron.m.bray@gmail.com

* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*********************************************************************************/

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
