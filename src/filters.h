#pragma once

#include "rectDrawing.h"
#include "texture.h"
#include "shaders.h"
#include "utility.h" //settings
#include "waveField.h" //waveSeries


class filter : public rectDrawing {
protected:
    shader S;

    //bind textures and set uniforms
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


class displaceFilter : public filter, public settings{
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
