#include "shaders.h"
#include "loadShaders.h"

//TODO: errors and return value
bool shader::load(std::string vfile, std::string ffile) {
    id = loadShaders(vfile.c_str(), ffile.c_str() );
    return true;
}


bool shader::use() {
    glUseProgram(id);    

    //Set textures to their corresponding texture units:
    for(int i = 0; i < 16; i++) {
        std::string uniformName = "texture" + std::to_string(i);
        glUniform1i(glGetUniformLocation(id, uniformName.c_str()), i);
    }
}


bool shader::setUniform(std::string name, float value) {
    //set the value
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}    
