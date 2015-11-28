#include "LinUI.hpp"

bool entomoid::WindowBase::init()
{
    active_ = true;
    return true;
}

size_t entomoid::WindowBase::eventLoop()
{
    return 0;
}

void entomoid::WindowBase::shutdown()
{
    if (active_) {
        active_ = false;
    }


}