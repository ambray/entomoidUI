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

#include <sstream>
#include <iostream>
#include <string>
#include "Settings.hpp"

#ifdef _WIN32 
#include "win/WinUi.hpp"
#elif __ANDROID__
#include "android/AndUi.hpp"
#elif __linux__
#include "nix/LinUI.hpp"
#endif

namespace entomoid {
	class WindowBasic : public virtual WindowBase {
	public:
		template <typename... Args>
		WindowBasic(Args... args) {  }
		WindowBasic() {}
	};

	template <typename... Mixins>
	class Window : public virtual WindowBase, public Mixins... {
	public:

		virtual ~Window() 
		{
			shutdown();
		}

		template <typename... Args>
		Window(Args... args) : Mixins(args)...
		{
		}

		Window() : Mixins()...
		{}

		template <typename T, typename F>
		bool inline setEventFunc(T t, F callback, bool overwrite = true)
		{
			/// This function doesn't exist in WindowBase or Window, and is provided
			/// as an interface to allow custom event type registration via mixin
			return setEventListener(t, callback, overwrite);
		}
		
		template <EventType E>
		bool inline setEventFunc(EventCallback callback, bool overwrite = true) 
		{
			std::unique_lock<std::mutex> lock(eventLock_);
			if (!overwrite) {
				auto tmp = events_.find(E);
				if (tmp != events_.end())
					return false;
			}

			events_[E] = callback;
			return true;
		}

		template <typename T, typename F>
		bool inline removeEventFunc(T t, F f)
		{
			return removeEventListener(t, f);
		}

		template <EventType E>
		bool inline removeEventFunc()
		{
			std::unique_lock<std::mutex> lock(eventLock_);
			auto tmp = events_.find(E);
			if (tmp == events_.end())
				return false;

			events_.erase(tmp);
			return true;
		}

		virtual bool inline isActive() override 
		{
			return active_;
		}

		virtual std::shared_ptr<WindowSettings> inline getWindowObject() override
		{
			return winObj_;
		}
	};
}