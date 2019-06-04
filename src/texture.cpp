#include "texture.h"
#include "stb_image.h"
#include "waveField.h"
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //Set vertical wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    
    //Set minify and magnify interpolation
    // Options: GL_LINEAR, GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    
    
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


void texture::setAsTestPattern(int tx_i, int w, int h, int channels) {
    if(channels < 1)
        return;
    if(channels > 4)
        channels = 4;
    
    long long int size = w * h * channels;
    std::vector<float> pixels(size);

    waveSeries S[channels];
    for(int i=0; i<channels; i++) {
        S[i].randomize();
        S[i].normalize();
    }
    
    for(int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            float f_y = (float)y/h;
            float f_x = (float)x/w;
            float r,g,b,a;
            long long int i = (long long int)y * w * channels + (long long int)x * channels;

            for(int c=0; c<channels; c++) {
                pixels[i+c] = S[c].getAt(glm::vec2(f_x, f_y) );
            }
            
            
/*            
            r = S[0].getAt(glm::vec2(f_x, f_y));
            g = r * (-1);
            b = r*r;
            a = 1;
            
            if(channels == 1) {
                pixels[i] = (r+1)/2;
            }
            else{
                pixels[i] = r;
                pixels[i+1] = g;
                if(channels > 2)
                    pixels[i+2] = b;
                if(channels > 3)
                    pixels[i+3] = a;
            }
*/            
        }
    }
    setData(tx_i, w, h, (unsigned char*)&pixels[0], channels, GL_FLOAT);
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
