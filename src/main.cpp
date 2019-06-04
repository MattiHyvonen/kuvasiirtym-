#include "rectDrawing.h"
#include "texture.h"
#include "timing.h"
#include "shaders.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <limits>


int main() {
    
    srand(time(NULL));
    
    //Initialize GL context and create a window.
    globalContext.create(800, 600);

    //load and use shader
    shader S;
    S.load( "data/default.vertexShader",
            "data/default.fragmentShader"
          );
    S.use();

    //this needs to be called after a new shader is loaded to set the transform matrices.
    //TODO: make this happen automatically!
    globalContext.setAsRenderTarget();
    
    //Rectangle-drawing capabilities:
    rectDrawing R;
    R.create();
    
    //Textures:
    texture pic;
    pic.create();
    
    //load picture, use texture unit 0
    //pic.loadFromFile(0, "data/tux.jpg");
    pic.setAsTestPattern(0, 2048, 2048);

    //use the texture on texture unit 0
    pic.useTexture(0);
    
    //render the picture on screen
    setModelTransformation(100, 100, 400, 400);
    R.drawRectangle();
    
    //Start the clock and set target FPS
    globalClock.reset();
    globalClock.setPeriod_fps(60);
    
    //Flip buffers and check events first.
    //  Returns false when the context is closed.
    while(globalContext.update() ) {
        //sleep to match the target FPS
        globalClock.sleep();
    }

    return 0;
}
