#pragma once
#include <memory>
#include <Windows.h>
#include "WinUtils.hpp"



namespace entomoid {
	class WindowBase {
	private:
	protected:
		bool active_;
		std::shared_ptr<void> callback_;
		HWND window_;

	public:
		WindowBase() : active_(false) { }
		LRESULT WndFunc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		bool init();
		void shutdown();
	};
}