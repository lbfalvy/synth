#include "device.hpp"
#include <functional>

time_function signal_device::get_callback()
{
    using namespace std::placeholders;
    auto member_fn = &signal_device::operator();
    time_function f = std::bind(member_fn, this, _1);
    return f;
}

void signal_device_collection::operator()(PaTime now)
{
    for(signal_device* var : items)
    {
        (*var)(now);
    }
}