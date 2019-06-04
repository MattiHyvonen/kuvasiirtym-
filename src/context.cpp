#include "context.h"
#include "shaders.h"
#include <iostream>

context globalContext;

//Create a GLFW window and a GL context, make it current and clear.
//  Set viewport and view transformation
bool context::create(int w, int h) {

    //No need to create if it already exists.
    if(isCreated() ) {
        //TODO: check if it's good and maybe destroy if not?
        std::cout << "Context already created!\n";
        return false;
    }
    
    width = w;
    height = h;
    
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

    //bind framebuffer, set viewport and view transformation
    setAsRenderTarget();
    
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    created = true;
    return true;
}


int context::getWidth() {
    return width;
}


int context::getHeight() {
    return height;
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
    
    //always clear on update?
    //clear
    //glClear(GL_COLOR_BUFFER_BIT);
    
    return true;
}


//TODO: errors and return value
bool context::setAsRenderTarget() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height );
    setViewTransformation(width, height);
    return true;
}
