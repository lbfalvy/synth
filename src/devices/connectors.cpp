#include "devices/connectors.hpp"

void mono_multichannel::operator()(PaTime now)
{
    for (int i = 1; i < channels; i++)
    {
        *(first_element+i) = *(first_element);
    }
}