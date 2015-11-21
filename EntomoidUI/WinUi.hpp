#pragma once
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

#include <memory>
#include <thread>
#include <mutex>
#include <map>
#include <functional>
#include <Windows.h>
#include "Settings.hpp"
#include "WinUtils.hpp"


namespace entomoid {

	using EventCallback = std::function<void(EventObject&)>;

	class WindowBase {
	private:
		bool active_;
		std::shared_ptr<void> callback_;
	protected:
		std::shared_ptr<WindowSettings> winObj_;
		std::mutex eventLock_;
		std::map<EventType, EventCallback> events_;
		HWND window_;

	public:
		WindowBase() : active_(false), winObj_(new WindowSettings) { }
		LRESULT WndFunc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		virtual bool init();
		virtual size_t eventLoop();
		virtual bool isActive();
		virtual void shutdown();
		virtual bool setEventListener(EventType evt, EventCallback func, bool overwrite=true);
		std::shared_ptr<WindowSettings> getWindowObject();
	};
}