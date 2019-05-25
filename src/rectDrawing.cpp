#include "rectDrawing.h"
#include <array>
#include <iostream>

const std::array<glm::vec2, 6> rectangleVertices = {
    glm::vec2(-1.0f, -1.0f),
    glm::vec2( 1.0f, -1.0f),
    glm::vec2(-1.0f,  1.0f),
    
    glm::vec2( 1.0f, -1.0f),
    glm::vec2(-1.0f,  1.0f),
    glm::vec2( 1.0f,  1.0f)
};


bool rectDrawing::create(int width, int height) {
    std::cout << "Creating rectDrawing\n";
    if(globalContext.isCreated() == false) {
        std::cout << "Context not created!\n";
        return false;
    }
    
    //Generate vertex array object
    // and a buffer for the vertices
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vertexBuffer);

    
    //Bind the VAO and the buffer, and set the vertex data.
    // NOTE: this leaves it bound after the function!
    // To unbind: glBindBuffer(GL_ARRAY_BUFFER, 0); glBindVertexArray(0);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(   GL_ARRAY_BUFFER, 
                    sizeof(glm::vec2) * 6,
                    &rectangleVertices[0], 
                    GL_STATIC_DRAW
                );
    
    //define the vertex attribute for vertices and enable it
    // vertices are glm::vec2, ie. 2 floats
    glVertexAttribPointer(
                                0, 
                                2, 
                                GL_FLOAT, 
                                GL_FALSE, 
                                2*sizeof(float),
                                (void*)0
                            );
    glEnableVertexAttribArray(0);
    created = true;
    return true;
}


bool rectDrawing::isCreated(){
    return created;
}


bool rectDrawing::drawRectangle() {
    if(!isCreated())
        return false;
    glDrawArrays(GL_TRIANGLES, 0, 6);
    return true;
}
