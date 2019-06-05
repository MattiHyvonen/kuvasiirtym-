#pragma once

#include "rectDrawing.h"
#include "texture.h"
#include "shaders.h"
#include "utility.h" //settings
#include "waveField.h" //waveSeries
#include "timing.h" //timer


class filter : public rectDrawing {
protected:
    shader S;

    //bind textures and set uniforms before rendering
    // this is called by apply() before rendering
    // src is the color data
    virtual bool prepare(texture src);
    
    //render on dst using the filter
    bool render(fboTexture dst);
    //render on screen using the filter
    bool render();
    
public:
    void setShader(shader s);
    
    //render src on dst using the filter
    bool apply(texture src, fboTexture dst);
    //render src on screen using the filter
    bool apply(texture src);
};


class displaceFilter : public filter, public settings, public timer{
protected:
    //displacement map
    texture dmap;
    
    //random wave fluctuation for displacement:
    waveSeries W;
    glm::vec2 t; //wave-function variable
    
    //amount of displacement
    float displaceAmount = 0;

    //parameters: how the amount is changed
    float speed = 1;
    float magnitude = 1;

    //how long the transition takes, in seconds:
    float transitionTime = 30;
    
    //how long to wait before and after the transition, in seconds:
    float waitTime_start = 5;
    float waitTime_end = 5;
    
    //bind textures and set uniforms before rendering
    // this is called by apply() before rendering
    // src is the color data
    bool prepare(texture src);
    
    void updateDisplacement();

public:
    displaceFilter();
    
    bool generateMap();
    
    //load parameters from a settings file
    //  see utility.h
    bool loadSettings(std::string filename);
    
    //set src as the displacement map
    bool setMap(texture src);
};


class mixFilter : public filter, public settings, public timer{
    //an image that's mixed with another image
    texture image;
    
    //how long the mixing takes, in seconds:
    float transitionTime = 15;
    
    //how long to wait before and after the mixing, in seconds:
    float waitTime_start = 5;
    float waitTime_end = 5;
    
    bool finished = false;
    
    //bind textures and set uniforms before rendering
    // this is called by apply() before rendering
    // src is the color data
    bool prepare(texture src);    
    
public:
    void loadSettings(std::string settingsFile);
    void setImage(texture src);
    bool isFinished();
};
