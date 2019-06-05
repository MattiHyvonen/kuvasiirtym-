#include "filters.h"
#include "timing.h"
#include "waveField.h"
#include "context.h"

#include <time.h>
#include <stdlib.h>
#include <iostream>


int main() {
    
    srand(time(NULL));
    
    //Initialize GL context and create a window.
    globalContext.create(1920, 1080);

    //Textures
    texture pic;
    fboTexture fbo1;
    pic.create();

    //load picture, use texture unit 0
    pic.loadFromFile(0, "data/large.jpg");

    fbo1.create(0, pic.getWidth(), pic.getHeight() );

    //Filters
    displaceFilter F1, F2;
    F1.setShader(shader("data/default.vertexShader","data/default.fragmentShader") );
    F1.generateMap();
    F1.loadSettings("data/settings");
    
    F2.setShader(shader("data/default.vertexShader","data/default.fragmentShader") );
    F2.setMap(pic);
    F2.loadSettings("data/settings");
    
    //Start the clock and set target FPS
    globalClock.reset();
    globalClock.setPeriod_fps(25);

    //Flip buffers and check events first.
    //  Returns false when the context is closed.
    while(globalContext.update() ) {
        //render the picture on screen
        F1.apply(pic, fbo1);
        F2.apply(fbo1);

        //sleep to match the target FPS
        if(!globalClock.sleep())
            std::cout << "Lag!\n";
    }

    return 0;
}
