#include "textureLoader.h"
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


bool textureLoader::load(int tx_i, int w, int h, GLenum type, char* data) {

    if(!isCreated() ) {
        std::cout << "textureLoader not created!\n";
        return false;
    }
    
    std::cout   << "loading texture " << tx_i << ": " << w << "x" << h
                << "\n";
    
    if(tx_i < 0 || tx_i >= textures.size()) {
        std::cout << "bad texture index!\n";
        return false;
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
                    GL_RGBA,
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //NOTE: this leaves the texture unit active and the texture bound!
    return true;
}
