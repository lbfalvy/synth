#ifndef DEFS_H
#define DEFS_H

#include <functional>
#include <portaudio.h>
typedef std::function<void(PaTime)> time_function;

#endif