#pragma once

#include <string>
#include <functional>
#include <stdint.h>

#ifdef __ANDROID__

#elif __linux__
#include <xcb/xcb.h>
#elif _WIN32
#include <Windows.h>
#endif

namespace entomoid {


	enum class EventType {
		KeyEvent,
		MouseEvent,
		WindowEvent,
		QuitEvent,
		EventOther,
	};

	struct EventObject {
		EventType type;
	};

	using EventCallback = std::function<void(EventObject&)>;

#ifdef _WIN32 
	using WinRef = HWND;
#elif __ANDROID__
	using WinRef = void*;
#elif __linux__
    using WinRef = xcb_window_t;
#endif

	struct WindowSettings {
		std::string winTitle_;
		WinRef current_;
		size_t width_;
		size_t height_;
	};
}
