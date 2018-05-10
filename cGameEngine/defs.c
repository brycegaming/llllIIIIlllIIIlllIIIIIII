//defs.c
#include "include/defs.h"
#include "include/GenericSet.h"

void clearConsole(void){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sleep_ms(int milliseconds)
{
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(milliseconds * 1000);
#endif
}

unsigned char nextByte(FILE* file){
    char value;
    fread(&value, 1, 1, file);
    return value;
}

uint64_t getTimeMilliseconds(){
#ifdef WIN32
    SYSTEMTIME time;
    GetSystemTime(&time);
    LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;
    return time_ms;
#else
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (time.tv_sec * 1000) + (uint64_t)((double)time.tv_nsec / 1000000.0f);
#endif
}




