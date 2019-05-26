#pragma once
#define PI 3.14159265
#define TWO_PI 6.2831853
#include <stdlib.h>
#include <time.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>

//Clock class for FPS timing
class timer{
    std::chrono::system_clock::duration period;
    std::chrono::system_clock::time_point startTime;
public:
    void setPeriod_ms(int ms);
    bool setPeriod_fps(float fps);
    
    //sleep until 'period' has passed since last call to 'sleep()'
    bool sleep();
    
    //get time since last reset() call, in seconds
    float getTime();
    
    //set start time to current time
    void reset();
};
