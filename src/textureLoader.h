#pragma once
#include <array>
#include "context.h"

const int MAX_TEXTURES = 16;

//Contains a window and a GL context,
// a number of textures and the functions to access them.
class textureLoader{
    
    //GL ids to textures. The id corresponds to texture unit number.
    // ie. textures[i] is bound to texture unit i.
    std::array<unsigned int, MAX_TEXTURES> textures;
    bool created = false;

public:
    //create context and the textures
    // this doesn't allocate memory for pixels, 
    // just generates the GL objects
    bool create(int width = 640, int height = 512);
    bool isCreated();
    
    //Load the texture from pixel data
    // Arguments:
    //   texture_i: The texture unit to load. (0 to MAX_TEXTURES)
    //   w, h: Size of the given data, in pixels.
    //   type: Type of the given data (GL_UNSIGNED_BYTE, GL_FLOAT, &c.)
    // Resulting texture is always RGBA 32bit float,
    // with same size as the given data.
    // NOTE: memory allocation or data type is not checked in any way!
    bool load(int texture_i, int w, int h, GLenum type, char* data);
    
    void setAsTestPattern(int texture_i, int w, int h);
    
};
