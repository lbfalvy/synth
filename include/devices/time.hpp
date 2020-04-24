#ifndef DEVICES_TIME_HPP
#define DEVICES_TIME_HPP

#include "device.hpp"

class loop : public signal_device
{ // Loops internal's first few seconds
    public:
        signal_device* dev;
        PaTime* period;
        virtual void operator()(PaTime now) override;
};

class delay : public signal_device
{ // Offsets a device in time
    public:
        signal_device* dev;
        PaTime* delay;
        virtual void operator()(PaTime now) override;
};

struct timetable_entry
{
    signal_device* dev;
    PaTime* start;
    PaTime* end;
    bool* internal_time;
};

class scheduler : public signal_device
{ // Decides which device to execute based on time elapsed
    public:
        std::vector<timetable_entry> timetable;
        virtual void operator()(PaTime now) override;
};

#endif