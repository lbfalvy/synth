#ifndef DEVICES_CONNECTORS_HPP
#define DEVICES_CONNECTORS_HPP

#include "device.hpp"

class mono_multichannel : public signal_device
{
    public:
        float* first_element; // First element of the multichannel
        int channels; // Number of subsequent channels to clone to
        virtual void operator()(PaTime now) override;
};

#endif