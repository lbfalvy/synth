#include "devices/waves.hpp"
#include <iostream>

void sine::operator()(PaTime now)
{
    /*double angle = fmod( *frequency * now, 2 * M_PIl );
    *out = sin(angle);*/
   PaTime dt = now - internal_time ;
   internal_time = now;
   phase += *frequency * dt * 2*M_PIl;
   *out = sin(phase);
}

void square::operator()(PaTime now)
{
    *out = fmod( *frequency * now, 1 ) > 0.5 ? 1 : 0;
}

void saw::operator()(PaTime now)
{
    *out = fmod( *frequency * now, 1 ) * 2 - 1;
}