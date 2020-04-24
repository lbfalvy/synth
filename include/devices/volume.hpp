#ifndef DEVICES_VOLUME_HPP
#define DEVICES_VOLUME_HPP

#include "device.hpp"

class const_volume : public signal_device
{
    public:
        float* volume;
        float* sig;
        void operator()(PaTime now) override;
};

// Despite any "end" setting, the following devices extrapolate
// at times outside their settings

class linear_volume : public signal_device
{
    public:
        PaTime* start_time = nullptr; // 0 by default
        float* start_vol = nullptr; // 1 by default
        PaTime* end_time = nullptr;
        float* end_vol = nullptr; // 1 by default
        float* sig;
        void operator()(PaTime now) override;
};

class exp_volume : public signal_device
{
    public:
        PaTime* start_time = nullptr; // 0 by default
        float* start_vol = nullptr; // 1 by default
        PaTime* end_time = nullptr;
        float* end_vol = nullptr; // 1 by default
        float* sig;
        void operator()(PaTime now) override;
};

#endif