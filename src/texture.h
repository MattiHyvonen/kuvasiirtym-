#pragma once
#include <array>
#include "context.h"
#include <string>

class texture{
protected:
    unsigned int id;
    bool created = false;
    int width;
    int height;
public:    
    bool create();
    
    bool setData(   int tx_i,
                    int w, 
                    int h, 
                    unsigned char* data = 0,
                    int channels = 3,
                    GLenum type = GL_UNSIGNED_BYTE
                );
    
    bool loadFromFile(int texture_i, std::string filename);
    
    void setAsTestPattern(int texture_i, int w, int h);
    
    //use the texture on given texture unit
    bool useTexture(unsigned int textureUnit);
};


class fboTexture : public texture{
    unsigned int fbo_id;
public:
    bool create(int tx_i, int w, int h);
    bool useFBO();
};
