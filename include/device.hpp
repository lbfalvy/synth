#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <portaudio.h>
#include <vector>
#include "defs.hpp"

class signal_device
{
    public:
        virtual void operator()(PaTime now) = 0;
        time_function get_callback();
};

class signal_device_collection : public signal_device
{
    public:
        std::vector<signal_device*> items;
        virtual void operator()(PaTime now) override;
};

#endif