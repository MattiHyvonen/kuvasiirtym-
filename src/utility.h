#pragma once

#define PI 3.14159265
#define TWO_PI 6.2831853
#include <stdlib.h>
#include <time.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>

//Return a pseudorandom float, using the rand() function.
//  result is in the range 0...1:
float randomf();
//  result is in the range min...max:
float randomf(float min, float max);


//Generate a string of the format "path/to/frames/frame239.png",
//  counting the number as reference count up to max_frames.
//  After max_frames is reached, return empty string instead.
std::string generateFrameFilename(std::string path, 
                                  std::string extension,
                                  int max_frames = 10000
                                 );


//Separate a string by whitespace to a vector of strings
std::vector<std::string> separateString(std::string);


//Settings is a list of parameters with a name and a value (std::strings).
//  The settings file consists of name-value pairs.
//  Name and value are separated by whitespace.
//  The pairs (ie. parameters) are separated by newline.
class settings{
    std::unordered_map<std::string, std::string> contents;
public:
    //load settings from a file
    bool load(std::string filename);

    //save settings to a file
    bool save(std::string filename);
    
    //get parameter value as string
    std::string get(std::string parameterName);
    
    //get parameter value as int. Return 0 if not found
    int get_i(std::string parameterName);
    
    //get parameter value as float. Return 0 if not found
    float get_f(std::string parameterName);
    
    //Set parameter. If it doesn't exist, it is created.
    bool set(std::string parameterName, std::string newValue);
};
