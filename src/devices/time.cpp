#include "devices/time.hpp"
#include <math.h>

void loop::operator()(PaTime now)
{
    (*dev)(fmod(now, *period));
}

void delay::operator()(PaTime now)
{
    (*dev)(now - *delay);
}

void scheduler::operator()(PaTime now)
{
    for (int i = 0; i < timetable.size(); i++)
    {
        auto record = timetable[i];
        if (*record.start < now && now < *record.end)
        {
            (*record.dev)( record.internal_time ? 
                        now - *record.start : // Time since it started playing
                        now ); // Actual time
        }
    }
}