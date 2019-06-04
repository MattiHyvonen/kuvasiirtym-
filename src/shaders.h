#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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


//Set the view transformation matrix by the view dimensions
bool setViewTransformation(int width, int height);

//Set the model transformation matrix
//  This program is in 2D, so rotation is rotation in the XY plane, in radians.
//  (x,y) is the position of top left corner, in pixels.
//  Width & height are the desired render size of the texture, in pixels.
bool setModelTransformation(float x, float y, float width, float height, float rotation = 0);
