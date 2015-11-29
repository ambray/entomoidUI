#include "LinUI.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <xcb/xcb.h>

bool entomoid::WindowBase::init()
{
    uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t vals[2] = {0};

    if(xcb_connection_has_error(connection_))
        return false;

    screen_ = xcb_setup_roots_iterator(xcb_get_setup(connection_)).data;
    vals[0] = screen_->black_pixel;
    vals[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;

    winObj_->current_ = xcb_generate_id(connection_);
    auto cookie = xcb_create_window(connection_, XCB_COPY_FROM_PARENT, winObj_->current_,
                                    screen_->root,
                                    0, 0, 640, 480, 0,
                                    XCB_WINDOW_CLASS_INPUT_OUTPUT,
                                    screen_->root_visual, mask, vals);

    xcb_map_window(connection_, winObj_->current_);

    xcb_flush(connection_);

    active_ = true;
    return true;
}

size_t entomoid::WindowBase::eventLoop()
{
    xcb_generic_event_t* evt = nullptr;
    while((evt = xcb_wait_for_event(connection_))){
        if(!active_)
            return (size_t)0;

        switch(evt->response_type & ~0x80) {
        case XCB_KEY_PRESS: {
            auto k_ev = reinterpret_cast<xcb_key_press_event_t *>(evt);
            if(k_ev->detail == 9)
                return (size_t)0;
            break;
        }
        default:
            break;
        }
        delete evt;
    }
    return 0;
}

void entomoid::WindowBase::shutdown()
{
    if (active_) {
        xcb_disconnect(connection_);
        active_ = false;
    }


}