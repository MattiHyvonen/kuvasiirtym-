#pragma once
#include "GL.h"
#include <string>

class context{
private:
    //pointer to the GLFW window
    GLFWwindow* window;

    bool created = false;
    int width = 0;
    int height = 0;
    
public:
    //Create GLFW window and a GL context in it,
    // if a context doesn't already exists.
    // Return true if created, or if existing context is good.
    // Return false if couldn't create, 
    // or if existing context was not good.
    bool create(int width = 640, int height = 512);
    
    int getWidth();
    int getHeight();
    
    bool isCreated();
    
    //Return true if user closed window or ESC was pressed
    bool checkCloseEvent();
    
    //close the context and terminate GLFW
    void close();
    
    //Flip the buffers, clear and check events.
    // Return false if context was closed.
    bool update();
    
    //Bind frame buffer to the context
    //  Set viewport and view transformation
    bool setAsRenderTarget();
};

extern context globalContext;
