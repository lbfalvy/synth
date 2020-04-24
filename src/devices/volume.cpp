#include "devices/volume.hpp"
#include <cmath>

void const_volume::operator()(PaTime now)
{
    *sig *= *volume;
}

void linear_volume::operator()(PaTime now)
{
    float start_t = start_time == nullptr ? 0 : *start_time;
    float start_v = start_vol == nullptr ? 1 : *start_vol;
    float end_v = end_vol == nullptr ? 1 : *end_vol;
    float ratio = (now - start_t) / (*end_time - start_t);
    float volume = start_v + ratio * (end_v - start_v);
    *sig *= volume;
}

void exp_volume::operator()(PaTime now)
{
    PaTime start_t = start_time == nullptr ? 0 : *start_time;
    float start_v = start_vol == nullptr ? 1 : *start_vol;
    float end_v = end_vol == nullptr ? 1 : *end_vol;
    PaTime ratio = (now - start_t) / (*end_time - start_t);
    float volume = start_v * pow( end_v/start_v, ratio );
    *sig *= volume;
}