#include "rectDrawing.h"
#include "textureLoader.h"
#include <stdlib.h>
#include <time.h>

//TODO: template for any data type
void setUniform(std::string name, float value) {
    //get the shader
    GLint shader;
    glGetIntegerv(GL_CURRENT_PROGRAM, &shader);
    //set the value
    glUniform1f(glGetUniformLocation(shader, name.c_str()), value);
}


int main() {
    
    srand(time(NULL));
    
    globalContext.create(1024, 768);
    rectDrawing R;
    textureLoader T;
    
    R.create();
    T.create();

    T.load(0, "data/kuva1.jpg");
    T.load(1, "data/tux.jpg");
    float t = 0;
    float dt = 0.1;
    
    while(globalContext.update() ) {
        t += dt;
        float blend = sin(t);
        setUniform("blend", blend);
        
        R.drawRectangle();
    }

    return 0;
}
