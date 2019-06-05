#include "shaders.h"
#include "loadShaders.h"

//3D version
glm::mat4 getTransformationMatrix(glm::vec3 location,glm::vec3 rotation,glm::vec3 scale){
    glm::mat4 M(1.0f);

    M = glm::rotate(M, rotation.x, glm::vec3(1,0,0));
    M = glm::rotate(M, rotation.y, glm::vec3(0,1,0));
    M = glm::rotate(M, rotation.z, glm::vec3(0,0,1));

    M = glm::scale(M, scale);
    M = glm::translate(M, location);

    return M;
}


//2D version
glm::mat4 getTransformationMatrix(glm::vec2 location, float rotation,glm::vec2 scale){
    glm::mat4 M(1.0f);

    M = glm::scale(M, glm::vec3(scale.x, scale.y, 1) );
    M = glm::rotate(M, rotation, glm::vec3(0,0,1));
    M = glm::translate(M, glm::vec3(location.x, location.y, 0) );

    return M;
}


glm::mat4 getViewMatrix(float width, float height) {
    //result:   x = (0...width)  -> (-1... 1)
    //          y = (0...height) -> ( 1...-1)
    float xscale, yscale;
    if(width == 0) xscale = 0;
    else xscale = 2 / width;
    
    if(height == 0) yscale = 0;
    else yscale = 2 / height;
    
    glm::vec3 loc(-width/2, -height/2, 0);
    glm::vec3 rot(0, 0, 0);
    glm::vec3 scale(xscale, yscale, 1);
    
    return getTransformationMatrix(loc, rot, scale);
}


shader::shader() {}


shader::shader(std::string vfile, std::string ffile) {
    load(vfile, ffile);
}
    
    
//Read and compile the source files. Run use() to use the shader
//TODO: errors and return value
bool shader::load(std::string vfile, std::string ffile) {
    id = loadShaders(vfile.c_str(), ffile.c_str() );
    return true;
}


//Use the shader and set texture uniforms.
//TODO: errors and return value
bool shader::use() {
    glUseProgram(id);    

    //Set textures to their corresponding texture units:
    for(int i = 0; i < 16; i++) {
        std::string uniformName = "texture" + std::to_string(i);
        glUniform1i(glGetUniformLocation(id, uniformName.c_str()), i);
    }
    return true;
}


bool shader::setUniform(std::string name, float value) {
    //set the value
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}


//Set the view transformation matrix by the view dimensions
//TODO: errors and return value
bool setViewTransformation(int width, int height) {
    glm::mat4 M = getViewMatrix(width, height);
    
    //get the current shader
    int shaderID;
    glGetIntegerv(GL_CURRENT_PROGRAM, &shaderID);
    
    unsigned int M_location = glGetUniformLocation(shaderID, "viewMatrix");
    glUniformMatrix4fv(M_location, 1, GL_FALSE, &M[0][0]);
    return true;
}


//Set the model transformation matrix
//  This program is in 2D, so rotation is rotation in the XY plane, in radians.
//  Scale is 2-dimensional, separate for X and Y 
//  TODO: something wrong with the matrix math but it's working for now
bool setModelTransformation(float x, float y, float width, float height, float rotation) {
    glm::vec2 position( (x+width)/width, (y+height)/height);
    glm::vec2 scale(width/2, height/2);
    glm::mat4 M = getTransformationMatrix(position, rotation, scale);
    
    //get the current shader
    int shaderID;
    glGetIntegerv(GL_CURRENT_PROGRAM, &shaderID);
    
    unsigned int M_location = glGetUniformLocation(shaderID, "modelMatrix");
    glUniformMatrix4fv(M_location, 1, GL_FALSE, &M[0][0]);
    return true;
}
