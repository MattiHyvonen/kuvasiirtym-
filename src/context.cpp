#include "context.h"
#include <iostream>
#include "loadShaders.h"


bool context::contextExists = false;


//TODO: check if it's good
bool context::isGood() {
    return true;
}


bool context::create(int width, int height) {
    std::cout << "Creating context\n";
    
    if(contextExists) {
        //TODO: check if it's good and maybe destroy if not?
        return false;
    }
    
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
    int shaderProgram = loadShaders(
                                    "data/default.vertexShader",
                                    "data/default.fragmentShader"
                                    );
    glUseProgram(shaderProgram);
    
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
    
    //clear the screen and swap to try it
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    contextExists = true;
    return true;
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
    if(!contextExists) {
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
