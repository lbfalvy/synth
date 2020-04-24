#ifndef DEVICES_WAVES_HPP
#define DEVICES_WAVES_HPP

#include "device.hpp"
#include <cmath>

class sine : public signal_device
{
    private:
        PaTime phase;
        PaTime internal_time;
    public:
        float* frequency;
        float* out;
        void operator()(PaTime now) override;
};

class square : public signal_device
{
    public:
        float* frequency;
        float* out;
        void operator()(PaTime now) override;
};

class saw : public signal_device
{
    private:
        float value;
    public:
        float* frequency;
        float* out;
        void operator()(PaTime now) override;
};

#endif