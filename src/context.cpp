#include "context.h"
#include <iostream>
#include "loadShaders.h"

context globalContext;

bool context::create(int width, int height) {
    std::cout << "Creating context\n";
    
    //No need to create if it already exists.
    if(isCreated() ) {
        //TODO: check if it's good and maybe destroy if not?
        std::cout << "...already created!\n";
        return false;
    }
    
    //TODO: what if the required version is not supported?
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(  width, 
                                height, 
                                "kuvasiirtymä",
                                NULL, NULL
    );
    
    if(window == NULL)
        return false;
    
    glfwMakeContextCurrent(window);
    
    //NOTE: this needs to be after glfwMakeContextCurrent, why?
    glewInit();
    
    glViewport(0, 0, width, height);
    
    //Load shaders
    shader = loadShaders(
                                    "data/default.vertexShader",
                                    "data/default.fragmentShader"
                                    );
    glUseProgram(shader);
    
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
    
    //Set textures to their corresponding texture units:
    for(int i = 0; i < 16; i++) {
        std::string uniformName = "texture" + std::to_string(i);
        std::cout << "set uniform " << uniformName << ": " << i << "\n";
        glUniform1i(glGetUniformLocation(shader, uniformName.c_str()), i);
    }    
    
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    created = true;
    return true;
}


bool context::isCreated() {
    return created;
}


bool context::checkCloseEvent() {
    glfwPollEvents();

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwWindowShouldClose(window)) {
        return true;
    }
    return false;
}


void context::close() {
    
    std::cout << "Closing context\n";
    //don't close if there's no context
    if(!isCreated() ) {
        return;
    }
    
    glfwTerminate();
    window = NULL;
}


bool context::update() {
    //show what's been rendered
    glfwSwapBuffers(window);
    
    //close if there was a close event
    if(checkCloseEvent()) {
        close();
        return false;
    }
    
    //clear
    glClear(GL_COLOR_BUFFER_BIT);
    
    return true;
}
