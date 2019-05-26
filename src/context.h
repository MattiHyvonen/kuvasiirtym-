#pragma once
#include "GL.h"

class context{
protected:
    //pointer to the GLFW window
    //TODO: should this be private? Access from derived classes?
    GLFWwindow* window;
    
    //GL index to shader
    int shader;
    bool created = false;
    
public:
    //Create GLFW window and a GL context in it,
    // if a context doesn't already exists.
    // Return true if created, or if existing context is good.
    // Return false if couldn't create, 
    // or if existing context was not good.
    bool create(int width = 640, int height = 512);
    
    bool isCreated();
    
    //Return true if user closed window or ESC was pressed
    bool checkCloseEvent();
    
    //close the context and terminate GLFW
    void close();
    
    //Flip the buffers, clear and check events.
    // Return false if context was closed.
    bool update();
};

extern context globalContext;
