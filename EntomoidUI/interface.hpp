#pragma once

#include <memory>
#include "Settings.hpp"

namespace entomoid {
	class WindowInterface {
	public:
		virtual ~WindowInterface() {}
		virtual bool init() = 0;
		virtual size_t eventLoop() = 0;
		virtual bool isActive() = 0;
		virtual void shutdown() = 0;
		virtual bool setEventListener(EventType evt, EventCallback func, bool overwrite=true) = 0;
		virtual std::shared_ptr<WindowSettings> getWindowObject() = 0;
	};
}
