#pragma once

namespace entomoid {

#ifdef _WIN32 || _WIN64
	using WinRef = HWND;
#endif

	struct WindowSettings {
		std::string winTitle_;
		WinRef current_;
		size_t width_;
		size_t height_;
	};
}
