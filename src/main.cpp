#include "rectDrawing.h"
#include "textureLoader.h"
#include <stdlib.h>
#include <time.h>

int main() {
    
    srand(time(NULL));
    
    globalContext.create();
    rectDrawing R;
    textureLoader T;
    
    R.create();
    T.create();

    T.setAsTestPattern(0, 640, 512);
        
    while(globalContext.update() ) {
        R.drawRectangle();
    }

    return 0;
}
