#include "include/Time.h"

Timer TimerCreate(){
    Timer ret;

    ret.frames = 0;
    ret.currentFPS = 0;
    ret.startTime = getTimeMilliseconds();
    ret.currentTime = ret.startTime;

    return ret;
}

float TimerUpdate(Timer* timer){
    float delta = timer->currentTime;
    timer->frames++;

    timer->currentTime = getTimeMilliseconds();

    //a second has now passed
    if((timer->currentTime - timer->startTime) > 1000){
        timer->startTime = timer->currentTime;
        timer->currentFPS = timer->frames;
        timer->frames = 0;
    }

    return (timer->currentTime - delta) / 1000.0f;
}
