#pragma once
#include "GL.h"

class context{
protected:
    //Only 1 context is allowed at a time.
    // contextExists is true if there's already a context,
    // and new ones can't be created.
    static bool contextExists;
    
    //pointer to the GLFW window
    //TODO: should this be private? Access from derived classes?
    GLFWwindow* window;
    
public:
    //Return true if context is successfully created and can be used
    bool isGood();
    
    //Create GLFW window and a GL context in it.
    bool create(int width = 640, int height = 512);
    
    //Return true if user closed window or ESC was pressed
    bool checkCloseEvent();
    
    //close the context and terminate GLFW
    void close();
    
    //Flip the buffers, clear and check events.
    // Return false if context was closed.
    bool update();
};
