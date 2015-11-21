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
	EventCallback func;

	auto findCallback = [&](UINT m) -> bool {
		std::unique_lock<std::mutex> lock(eventLock_);

		auto tmp = events_.find(utils::platformTranslateEvent(m));
		if (events_.end() == tmp)
			return false;

		func = tmp->second;
		return true;
	};

	if (WM_DESTROY == msg) {
		PostQuitMessage(0);
		return 0;
	}
	
	if (findCallback(msg) && func) {
		// TODO: set up event objects!
		EventObject obj;
		obj.type = utils::platformTranslateEvent(msg);
		func(obj);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}

bool entomoid::WindowBase::init()
{
	WNDCLASSEXA wc = { 0 };

	try {
		windowClassName_ = utils::platformGetUniqueId();
		callback_ = utils::platformGetCallback(this, &WindowBase::WndFunc);

		wc.cbSize = sizeof(wc);
		wc.style = 0;
		wc.lpfnWndProc = reinterpret_cast<WNDPROC>(callback_.get());
		wc.hInstance = GetModuleHandle(nullptr);
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 2);
		wc.lpszClassName = windowClassName_.c_str();

		if (!RegisterClassEx(&wc)) {
			DEBUG_MESSAGE("Unable to register class!");
			return false;
		}

		if (nullptr == (window_ = CreateWindowEx(0, windowClassName_.c_str(), "Title.", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, GetModuleHandle(nullptr), nullptr))) {
			DEBUG_MESSAGE("Failed to create Window!");
			return false;
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

size_t entomoid::WindowBase::eventLoop()
{
	if (!active_)
		return 0;

	MSG msg = { 0 };
	while (true) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (WM_QUIT == msg.message)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

bool entomoid::WindowBase::isActive()
{
	return active_;
}

void entomoid::WindowBase::shutdown()
{
	if (active_)
		DestroyWindow(window_);
}

bool entomoid::WindowBase::setEventListener(EventType evt, EventCallback func, bool overwrite)
{
	std::unique_lock<std::mutex> lock(eventLock_);
	if (!overwrite) {
		auto tmp = events_.find(evt);
		if (tmp != events_.end())
			return false;
	}

	events_[evt] = func;
	return true;
}

std::shared_ptr<entomoid::WindowSettings> entomoid::WindowBase::getWindowObject()
{
	return winObj_;
}
