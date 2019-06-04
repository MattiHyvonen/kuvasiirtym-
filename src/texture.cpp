#include "texture.h"
#include "stb_image.h"
#include <iostream>
#include <vector>

bool texture::create() {
    if(globalContext.isCreated() == false) {
        std::cout << "Context not created!\n";
        return false;
    }
    
    glGenTextures(1, &id);
    created = true;
    return true;
}


int texture::getWidth() {
    return width;
}


int texture::getHeight() {
    return height;
}


//TODO: safer container version
bool texture::setData(  int tx_i,
                        int w, 
                        int h, 
                        unsigned char* data,
                        int channels,
                        GLenum type
                     ) 
{
    if(created == false) {
        std::cout << "Texture not created!\n";
        return false;
    }
    
    //there are 15 texture units
    if(tx_i < 0 || tx_i > 15) {
        std::cout << "bad texture index!\n";
        return false;
    }    
    
    width = w;
    height = h;

    GLenum format; //format of pixel data, defined by the number of channels
    
    switch(channels) {
        case 4:
            format = GL_RGBA;
            break;
        default:
            std::cout   << "Bad number of channels: " << channels
                        << "! 3 assumed\n";
        case 3:
            format = GL_RGB;
            break;
        case 2:
            format = GL_RG;
            break;
        case 1:
            format = GL_RED;
    }
    
    //Bind the texture in the corresponding texture unit
    glActiveTexture(GL_TEXTURE0 + tx_i);
    glBindTexture(GL_TEXTURE_2D, id);
       
    //Set the data
    glTexImage2D(   GL_TEXTURE_2D,
                    0,
                    GL_RGBA32F,
                    w,
                    h,
                    0,
                    format,
                    type,
                    data
                );
    
    //TODO: mipmap
                
    //Set horizontal wrapping 
    // Options: GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //Set vertical wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    //Set minify and magnify interpolation
    // Options: GL_LINEAR, GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);    
    
    return true;
}


bool texture::loadFromFile(int tx_i, std::string filename) {
    if(tx_i < 0 || tx_i > 15) {
        std::cout << "bad texture index!\n";
        return false;
    }
    
    int width, height, channels;
    unsigned char* data = stbi_load(    filename.c_str(), 
                                        &width, 
                                        &height, 
                                        &channels, 
                                        0
                                   );
    setData(tx_i, width, height, data, channels, GL_UNSIGNED_BYTE);
    
    stbi_image_free(data);
    
    //TODO: return value
    return true;    
}


void texture::setAsTestPattern(int tx_i, long long int w, long long int h) {
    long long int size = w * h * 4;
    std::vector<unsigned char> pixels(size);
    long long int max_i = 0;
    for(long long int y=0; y<h; y++) {
        for(long long int x=0; x<w; x++) {
            float f_y = (float)y/h;
            float f_x = (float)x/w;
            float r,g,b,a;
            long long int i = 4*(y*w + x);
            
            max_i = i;
            
            r = f_x;
            g = f_y;
            b = 0.5;
            a = 1.0;
            
            unsigned char c_r = r * 256;
            unsigned char c_g = g * 256;
            unsigned char c_b = b * 256;
            unsigned char c_a = a * 256;
            
            pixels[i] = c_r;
            pixels[i+1] = c_g;
            pixels[i+2] = c_b;
            pixels[i+3] = c_a;
            
        }
    }
    setData(tx_i, w, h, &pixels[0], 4, GL_UNSIGNED_BYTE);
}


//TODO: return value?
bool texture::useTexture(unsigned int tx_i) {
    //Bind the texture in the corresponding texture unit
    glActiveTexture(GL_TEXTURE0 + tx_i);
    glBindTexture(GL_TEXTURE_2D, id);
    return true;
}


bool fboTexture::create(int tx_i, int w, int h) {
    glGenFramebuffers(1, &fbo_id);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    
    texture::create();
    setData(tx_i, w, h, 0, 4, GL_FLOAT);
    
    //attach texture as color attachment 0
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);
    
    //reset frame buffer binding
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}


//Start using the texture as the rendering target.
//  Set viewport to the texture's size.
bool fboTexture::useFBO() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    glViewport(0, 0, width, height);
}
