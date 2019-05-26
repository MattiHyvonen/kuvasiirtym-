#pragma once
#include <string>

class shader{ 
    //GL index to shader
    int id;

public:
    bool load(std::string vfile, std::string ffile);
    bool use();
    
    //Set a float uniform in the current shader. 
    //TODO: template for any data type    
    bool setUniform(std::string name, float value);    
};

