#include "executor.hpp"
#include <iostream>
#include <string.h>

int executor::instances = 0;

executor::executor(time_function cb, int sr, int in, int out) : 
    sample_rate(sr), input_count(in), output_count(out), worker(cb)
{
    PaError err = Pa_OpenDefaultStream( &stream, in, out, paFloat32, sr, 
                                        paFramesPerBufferUnspecified, 
                                        pa_callback, this );
    if ( err != paNoError ) throw err;
}

executor::executor(time_function cb, int sr, PaStreamParameters* in, 
                                              PaStreamParameters* out) :
    sample_rate(sr), worker(cb)
{
    if (in == nullptr) input_count = 0;
    else input_count = in->channelCount;
    if (out == nullptr) output_count = 0;
    else output_count = out->channelCount;
    PaError err = Pa_OpenStream( &stream, 
                                 in, out, 
                                 sr, paFramesPerBufferUnspecified, 
                                 paNoFlag, 
                                 pa_callback, this);
    if ( err != paNoError ) throw err;
}

executor::~executor()
{
    if ( !Pa_IsStreamStopped( stream ) ) stop();
}

void executor::start()
{
    PaError err = Pa_StartStream(stream);
    if ( err != paNoError ) throw err; 
}

void executor::stop()
{
    PaError err = Pa_StopStream(stream);
    if ( err != paNoError ) throw err;
}

void executor::close()
{
    if ( !Pa_IsStreamStopped( stream ) ) stop();
    PaError err = Pa_CloseStream(stream);
    if ( err != paNoError ) throw err;
}

int executor::pa_callback(const void *input, void *output, 
                        unsigned long frameCount,
                        const PaStreamCallbackTimeInfo *timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData)
{;
    float* next_in = (float*)input;
    float* next_out = (float*)output;
    executor* ex = (executor*)userData;
    PaTime now = ex->now;
    for (unsigned long i = 0; i < frameCount; i++)
    {
        // Copy all channels to the inputs buffer
        if (ex->input_count != 0) memcpy(ex->inputs, next_in, 
                                        sizeof(float) * ex->input_count);
        // Roll the simulation
        try {
            ex->worker(now);
        } catch(...) {
            return paAbort;
        }
        
        // Copy all channels from the outputs buffer
        if (ex->output_count != 0) memcpy(next_out, ex->outputs, 
                                         sizeof(float) * ex->output_count);
        // Step in the buffers
        next_in += ex->input_count;
        next_out += ex->output_count;
        // Update time
        now += 1.0f / ex->sample_rate; // Seconds in one frame
    }
    ex->now = now;
    return paContinue;
}