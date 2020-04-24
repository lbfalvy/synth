#include "defs.hpp"
#include "executor.hpp"
#include "devices/waves.hpp"
#include "devices/connectors.hpp"
#include "devices/volume.hpp"
#include "devices/time.hpp"
#include <functional>
#include <portaudio.h>
#include <math.h>
#include <iostream>
#include <vector>

int main() {
    PaError err = Pa_Initialize();
    if ( err != paNoError )
    {
        std::cerr << Pa_GetErrorText( err ) << std::endl;
        return -1;
    }
    // Set up instrument
    float frequency = 200;
    float data[2];
    sine mywave;
    mywave.frequency = &frequency;
    mywave.out = data;
    exp_volume vol;
    vol.end_vol = new float(0.1);
    vol.end_time = new PaTime(1);
    vol.sig = data;
    loop myloop;
    myloop.period = new PaTime(2);
    myloop.dev = &vol;
    mono_multichannel split;
    split.first_element = data;
    split.channels = 2;
    signal_device_collection rack;
    rack.items = {&mywave, &myloop, &split};
    // Portaudio stuff
    try
    {
        executor ex(rack.get_callback(), 48000, 0, 2);
        ex.outputs = data;
        // Play
        ex.start();
        std::cout << "Press Return to continue..." << std::endl;
        std::cout.flush();
        system("read");
        // Finish
        ex.close();
        Pa_Terminate();
    }
    catch(PaError pa_error)
    {
        std::cerr << Pa_GetErrorText( pa_error ) << std::endl;
        return -1;
    }
    return 0;
}