#include "textureLoader.h"
#include "stb_image.h"
#include <iostream>

bool textureLoader::create(int width, int height) {
    std::cout << "creating textureLoader\n";
    
    if(globalContext.isCreated() == false) {
        std::cout << "Context not created!\n";
        return false;
    }
    
    //Generate textures:
    // textures.size(): the number of texture indices in array 'textures'
    glGenTextures(textures.size(), &textures[0]);

    created = true;
    return true;
}


bool textureLoader::isCreated(){
    return created;
}


bool textureLoader::load(   int tx_i, 
                            int w, 
                            int h, 
                            unsigned char* data, 
                            int channels, 
                            GLenum type
                        ) 
{
    if(!isCreated() ) {
        std::cout << "textureLoader not created!\n";
        return false;
    }
    
    std::cout   << "loading texture " << tx_i << ": " << w << "x" << h
                << " with " << channels << " channels\n";
    
    if(tx_i < 0 || tx_i >= textures.size()) {
        std::cout << "bad texture index!\n";
        return false;
    }
    
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
    glBindTexture(GL_TEXTURE_2D, textures[tx_i]);
       
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
    
    //NOTE: this leaves the texture unit active and the texture bound!
    return true;
}

//TODO: some images don't work right
//  maybe something with the type (GL_UNSIGNED_BYTE)
//TODO: 16-bit tga?
bool textureLoader::load(int tx_i, std::string filename) {
    if(tx_i < 0 || tx_i >= textures.size()) {
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
    load(tx_i, width, height, data, channels, GL_UNSIGNED_BYTE);
    
    stbi_image_free(data);
    
    //TODO: return value
    return true;
}
    
    
void textureLoader::setAsTestPattern(int texture_i, int w, int h) {
    int size = w * h * 4;
    unsigned char pixels[size];
    
    for(int y=0; y<h; y++) {
        for(int x=0; x<w; x++) {
            float f_y = (float)y/h;
            float f_x = (float)x/w;
            float r,g,b,a;
            int i = 4*(y*w + x);
            
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
    
    load(0, w, h, pixels, 4, GL_UNSIGNED_BYTE);
}
