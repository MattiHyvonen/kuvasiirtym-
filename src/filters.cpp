#include "filters.h"
#include <iostream>

void filter::setShader(shader s) {
    S = s;
}
    
    
bool filter::prepare(texture src) {
    //use src on texture unit 0
    src.useTexture(0);
    
    return true;
}
    
    
bool filter::render(fboTexture dst) {
    //NOTE: this leaves the FBO bound as the render target and the view set to it!
    // Call context::setAsRenderTarget() to set it to screen
    dst.useFBO();
    setViewTransformation(dst.getWidth(), dst.getHeight()); //see shaders.h
    setModelTransformation(0, 0, dst.getWidth(), dst.getHeight());
    drawRectangle();
    return true;
}
    
    
bool filter::render() {
    globalContext.setAsRenderTarget();
    setModelTransformation(0, 0, globalContext.getWidth(), globalContext.getHeight());
    drawRectangle();
    return true;
}
    
    
bool filter::apply(texture src, fboTexture dst) {
    //If not created (buffers &c), try to create. If fails, abort.
    //  see rectDrawing.h
    if(!isCreated() )
        if(!create() )
            return false;
    if(!S.use() )
        return false;
    
    prepare(src);
    render(dst);
    
    return true;
}
    
    
bool filter::apply(texture src) {
    //If not created (buffers &c), try to create. If fails, abort.
    //  see rectDrawing.h
    if(!isCreated() )
        if(!create() )
            return false;
    if(!S.use() )
        return false;
    
    prepare(src);
    render();
    return true;
}


bool displaceFilter::prepare(texture src) {
    //Use texture unit 0 for color data and 1 for displacement map
    updateDisplacement();
    src.useTexture(0);
    dmap.useTexture(1);
        
    return true;
}


void displaceFilter::updateDisplacement() {
    const float y = 0.123454321;
    
    //Constant level factors to scale the magnitude and speed
    //  so that default level is 1 in the settings file.
    const float mLevel = 1;
    const float speedLevel_x = 1;
    const float speedLevel_y = 0.123454321;
    
    float tTime = getTime() - waitTime_start;
    float tLevel;
    
    if(tTime < 0)
        tLevel = 0;
    else if(tTime < transitionTime)
        tLevel = (tTime / transitionTime) * PI;
    else {
        tLevel = PI;
    }
    
    float m = mLevel * magnitude;
    glm::vec2 dt(speed * speedLevel_x, speed * speedLevel_y);
    
    t += dt;
    displaceAmount += m * W.getAt(t);
    S.setUniform("displacement", sin(tLevel) * displaceAmount);
}


displaceFilter::displaceFilter() {
    W.randomize();
    W.normalize();    
}


bool displaceFilter::generateMap() {
    dmap.create();
    dmap.setAsTestPattern(1, 512, 512, 2);
    return true;
}


bool displaceFilter::loadSettings(std::string filename) {
    if(!settings::load(filename))
        return false;
    
    if(exists("displaceSpeed") )
        speed = get_f("displaceSpeed");
    if(exists("displaceMagnitude") )
        magnitude = get_f("displaceMagnitude");

    int harmonics = 10;
    int waveNumber = 10;
    
    if(exists("displaceHarmonics") )
        harmonics = get_i("displaceHarmonics");
    if(exists("displaceWavenumber") )
        waveNumber = get_i("displaceWavenumber");
    
    if(exists("transitionTime"))
        transitionTime = get_f("transitionTime");
    if(exists("waitTime_start"))
        waitTime_start = get_f("waitTime_start");
    if(exists("waitTime_end"))
        waitTime_end = get_f("waitTime_end");    
    
    //start the clock
    reset();
    
    W.randomize(harmonics, waveNumber);
    W.normalize();
    
    return true;
}    
    
    
bool displaceFilter::setMap(texture src) {
    dmap = src;
    return true;
}


bool mixFilter::prepare(texture src) {
    if(finished) {
        S.setUniform("blend", 1);
        src.useTexture(0);
        image.useTexture(1);        
        return true;
    }
    
    float mixTime = getTime() - waitTime_start;
    float mix;
    
    if(mixTime < 0)
        mix = 0;
    else if(mixTime < transitionTime)
        mix = mixTime / transitionTime;
    else {
        mix = 1;
        finished = true;
    }
    
    std::cout << "blend: " << mix << "\n";
    
    S.setUniform("blend", mix);
    src.useTexture(0);
    image.useTexture(1);
    return true;
}


void mixFilter::loadSettings(std::string file) {
    //load settings from file to settings object
    load(file);
    
    //get parameters from the settings object
    if(exists("transitionTime"))
        transitionTime = get_f("transitionTime");
    if(exists("waitTime_start"))
        waitTime_start = get_f("waitTime_start");
    if(exists("waitTime_end"))
        waitTime_end = get_f("waitTime_end");
    
    //start the clock
    reset();
}


void mixFilter::setImage(texture src) {
    image = src;
}


bool mixFilter::isFinished() {
    return finished;
}

