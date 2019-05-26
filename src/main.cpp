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

    T.load(0, "data/tux.jpg");  
    
    while(globalContext.update() ) {
        R.drawRectangle();
    }

    return 0;
}
