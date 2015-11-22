#pragma once

#include <string>
#include <functional>
#include <stdint.h>

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
#endif

	struct WindowSettings {
		std::string winTitle_;
		WinRef current_;
		size_t width_;
		size_t height_;
	};
}
