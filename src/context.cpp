#include "context.h"
#include <iostream>

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


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
    // TODO: error checking and logging
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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
