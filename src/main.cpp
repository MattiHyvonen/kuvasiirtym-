#include "rectDrawing.h"
#include "textureLoader.h"
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
    
    //Texture loading:
    textureLoader T;    
    T.create();    
    
    //load 2 images, to texture units 0 and 1
    T.load(0, "data/kuva1.jpg");
    T.load(1, "data/tux.jpg");

    //Start the clock and set target FPS
    timer t;
    t.reset();
    t.setPeriod_fps(60);
    
    //frequency of blending
    float f = 3;

    //Flip buffers and check events first.
    //  Returns false when the context is closed.
    while(globalContext.update() ) {

        //Set blend factor, 0...1
        float blend = sin(t.getTime()*f);
        S.setUniform("blend", blend);
        
        R.drawRectangle();
        
        //sleep to match the target FPS
        t.sleep();
    }

    return 0;
}
