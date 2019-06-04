#include "rectDrawing.h"
#include "texture.h"
#include "timing.h"
#include "shaders.h"
#include "waveField.h"
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
    
    //Textures: a picture and a displace map
    texture pic, dmap;
    pic.create();
    dmap.create();
    
    //load picture, use texture unit 0
    pic.loadFromFile(0, "data/kuva1.jpg");
    
    //create displace map, use texture unit 0
    dmap.setAsTestPattern(0, 600, 400, 2);

    //use the picture on texture unit 0, and the map on unit 1
    pic.useTexture(0);
    dmap.useTexture(1);
    
    setModelTransformation(0, 0, globalContext.getWidth(), globalContext.getHeight());
    
    //Start the clock and set target FPS
    globalClock.reset();
    globalClock.setPeriod_fps(25);
    
    //random fluctuation for displacement value:
    float dSpeed = 0.1;
    float dMagnitude = 0.005;
    float dAmount = 0;
    waveSeries dS;
    dS.randomize(20, 20);
    dS.normalize();
    
    //Flip buffers and check events first.
    //  Returns false when the context is closed.
    while(globalContext.update() ) {
        //render the picture on screen
        float t = globalClock.getTime() * dSpeed;
        dAmount += dMagnitude * dS.getAt(glm::vec2(t, 0.1219769*t) );
        //dmap.setAsTestPattern(1, 600, 400, 2);
        S.setUniform("displacement", dAmount);
        R.drawRectangle();
        //sleep to match the target FPS
        if(!globalClock.sleep())
            std::cout << "Lag!\n";
    }

    return 0;
}
