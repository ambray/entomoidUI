#pragma once

#include <memory>
#include <mutex>
#include <map>
#include <functional>
#include <xcb/xcb.h>
#include "../interface.hpp"
#include "../Settings.hpp"

namespace entomoid {
    class WindowBase : public WindowInterface {
    private:
        xcb_connection_t* connection_;
        xcb_screen_t* screen_;
    protected:
        bool active_;
        std::shared_ptr<WindowSettings> winObj_;
        std::mutex eventLock_;
        std::map<EventType, EventCallback> events_;

    public:
        WindowBase() : active_(false), winObj_(new WindowSettings), connection_(xcb_connect(nullptr, nullptr))
        {}
        virtual ~WindowBase() {}
        virtual bool init();
        virtual size_t eventLoop();
        virtual void shutdown();
    };
}