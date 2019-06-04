#include "rectDrawing.h"
#include "texture.h"
#include "timing.h"
#include "shaders.h"
#include <stdlib.h>
#include <iostream>


int main() {
    
    //Initialize GL context and create a window.
    globalContext.create(800, 600);

    //load and use shader
    shader S;
    S.load( "data/default.vertexShader",
            "data/default.fragmentShader"
          );
    S.use();
        
    //Rectangle-drawing capabilities:
    rectDrawing R;
    R.create();
    
    //Textures:
    texture pic;
    pic.create();
    
    //load picture, use texture unit 0
    pic.loadFromFile(0, "data/tux.jpg");

    //use the texture on texture unit 0
    pic.useTexture(0);
    
    //render the picture on screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 800, 600);
    setViewTransformation(800, 600);
    setModelTransformation(100, 100, 400, 400);
    R.drawRectangle();
    
    //Start the clock and set target FPS
    timer t;
    t.reset();
    t.setPeriod_fps(60);
    
    //Flip buffers and check events first.
    //  Returns false when the context is closed.
    while(globalContext.update() ) {
        //sleep to match the target FPS
        t.sleep();
    }

    return 0;
}
