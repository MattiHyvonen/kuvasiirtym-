#include "rectDrawing.h"
#include "textureLoader.h"

int main() {
    createMainWindow();
    rectDrawing R;
    textureLoader T;
    
    R.create();
    T.create();
    
    while(globalContext.update() )
        R.drawRectangle();

    return 0;
}
