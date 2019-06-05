#include "filters.h"
#include "timing.h"
#include "waveField.h"
#include "context.h"
#include "utility.h"

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>


class mainSettingsC : public settings{
public:
    std::string pic1_file;
    std::string pic2_file;
    std::string pic3_file;
    
    int randomSeed = 0;
    
    void loadSettings() {
        load("data/transitionA.settings");
        if(exists("kuva1"))
            pic1_file = get("kuva1");
        if(exists("kuva2"))
            pic2_file = get("kuva2");
        if(exists("kuva3"))
            pic3_file = get("kuva3");
        
        //randomize random seed if it is not in the settings
        randomSeed = time(NULL);
        
        if(exists("randomSeed")) {
            if(get("randomSeed") != "" && get("randomSeed") != "none")
                randomSeed = get_i("randomSeed");
        }
        
        std::cout << "Random seed: " << randomSeed << "\n";
    }
    
} mainSettings;


int main() {
    
    mainSettings.loadSettings();
    srand(mainSettings.randomSeed);
        
    //Initialize GL context and create a window.
    globalContext.create(1920, 1080);

    //Textures
    texture pic1, pic2, pic3;
    fboTexture fbo1, fbo2, fbo3;
    pic1.create();
    pic2.create();
    pic3.create();

    //load picture, use texture unit 0
    pic1.loadFromFile(0, mainSettings.pic1_file);
    pic2.loadFromFile(0, mainSettings.pic2_file);
    pic3.loadFromFile(0, mainSettings.pic3_file);

    fbo1.create(0, pic1.getWidth(), pic1.getHeight() );
    fbo2.create(0, pic1.getWidth(), pic1.getHeight() );
    fbo3.create(0, pic1.getWidth(), pic1.getHeight() );

    //Filters
    displaceFilter dis1, dis2, dis3, dis4, dis5, dis6;
    mixFilter mix1;
    
    dis1.setShader(shader("data/default.vertexShader","data/default.fragmentShader") );
    dis1.generateMap();
    dis1.loadSettings("data/displace1.settings");
    
    dis2.setShader(shader("data/default.vertexShader","data/default.fragmentShader") );
    dis2.generateMap();
    dis2.loadSettings("data/displace2.settings");

    dis3.setShader(shader("data/default.vertexShader","data/default.fragmentShader") );
    dis3.setMap(pic2);
    dis3.loadSettings("data/displace3.settings");
    
    dis4.setShader(shader("data/default.vertexShader","data/default.fragmentShader") );
    dis4.generateMap();
    dis4.loadSettings("data/displace1.settings");
    
    dis5.setShader(shader("data/default.vertexShader","data/default.fragmentShader") );
    dis5.generateMap();
    dis5.loadSettings("data/displace2.settings");

    dis6.setShader(shader("data/default.vertexShader","data/default.fragmentShader") );
    dis6.setMap(pic2);
    dis6.loadSettings("data/displace3.settings");

    mix1.setShader(shader("data/default.vertexShader", "data/mix.fragmentShader") );
    mix1.setImage(pic2);
    mix1.loadSettings("data/transitionA.settings");
    
    //Start the clock and set target FPS
    globalClock.reset();
    globalClock.setPeriod_fps(25);

    //Flip buffers and check events first.
    //  Returns false when the context is closed.
    while(globalContext.update() ) {
        //do 3 passes of displacement on pic1, render final result on fbo3
        dis1.apply(pic1, fbo1);
        dis2.apply(fbo1, fbo2);
        dis3.apply(fbo2, fbo3);
        
        //do 3 passes of displacement on pic2, render final result on fbo1
        dis1.apply(pic2, fbo1);
        dis2.apply(fbo1, fbo2);
        dis3.apply(fbo2, fbo1);
        
        //mix fbo3 to pic2, render on screen
        mix1.setImage(fbo1);
        mix1.apply(fbo3);

        //sleep to match the target FPS
        if(!globalClock.sleep())
            std::cout << "Lag!\n";
    }

    return 0;
}
