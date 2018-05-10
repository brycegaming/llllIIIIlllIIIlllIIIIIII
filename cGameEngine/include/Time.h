#ifndef INCLUDE_TIME
#define INCLUDE_TIME

#include "defs.h"

/**
 * holds information about the timer state
 * */
typedef struct timer{
    int currentFPS;
    int frames;

    uint64_t startTime;
    uint64_t currentTime;
}Timer;

/**
 * inits the timer
 * */
Timer TimerCreate();

/**
 * updates the timer with the new system time
 * returns the amount of time that has passed since that update in seconds
 * */
float TimerUpdate(Timer* timer);

#endif
