#include "timing.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>


timer globalClock;


void timer::setPeriod_ms(int period_ms) {
    typedef std::chrono::system_clock::duration sysduration;
    typedef std::chrono::milliseconds milliseconds;
    
    period = std::chrono::duration_cast<sysduration> (milliseconds(period_ms));
}


bool timer::setPeriod_fps(float fps) {
    if(fps <= 0)
        return false;
    float ms = 1000/fps;
    setPeriod_ms(ms);
    return true;
}


void printDuration(std::chrono::system_clock::duration d) {
    typedef std::chrono::milliseconds milliseconds;

    milliseconds duration_ms = std::chrono::duration_cast<milliseconds>(d);
    std::cout << duration_ms.count() << " ms\n";
}


bool timer::sleep() {
    typedef std::chrono::system_clock::time_point timePoint;
    typedef std::chrono::system_clock::duration duration;
    
    static timePoint lastCall;
    timePoint now = std::chrono::system_clock::now();
    timePoint periodEnd = lastCall + period;
    
    if(periodEnd < now) {
        lastCall = now;
        return false;
    }
    
    else {
        duration sleepTime = periodEnd - now;
        std::this_thread::sleep_until(periodEnd);
        lastCall = periodEnd;
        return true;
    }
}


float timer::getTime() {
    //precision is milliseconds. TODO: better precision!
    //TODO: something wrong with the duration cast
    typedef std::chrono::system_clock::time_point timePoint;
    typedef std::chrono::system_clock::duration duration;
    typedef std::chrono::milliseconds milliseconds;
    timePoint now = std::chrono::system_clock::now();

    duration elapsedTime = now - startTime;
    duration elapsedTime_ms = std::chrono::duration_cast<milliseconds>(elapsedTime);
    
    return ((float)(elapsedTime_ms.count() ) / 1000000000.0f);
}


void timer::reset() {
    startTime = std::chrono::system_clock::now();
}
