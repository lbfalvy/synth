#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "defs.hpp"
#include <portaudio.h>


class executor {
private:
    static int instances;
    void initialize_if_needed();
public:
    PaTime now = 0;
    PaStream *stream;
    int sample_rate;
    int input_count;
    int output_count;
    float* inputs = nullptr;
    float* outputs = nullptr;
    time_function worker;
    static int pa_callback( const void *input, void *output, 
                            unsigned long frameCount,
                            const PaStreamCallbackTimeInfo *timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData);
    executor(time_function cb, int sr, int in, int out);
    executor(time_function cb, int sr, PaStreamParameters* input,
                                       PaStreamParameters* output);
    ~executor();
    void close();
    void stop();
    void start(); 
};

#endif