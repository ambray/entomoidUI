#include "LinUI.hpp"
#include <unistd.h>

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
    using namespace std::literals;
    while(true){
       sleep(1000);
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