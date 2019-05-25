#include "rectDrawing.h"

int main() {
    rectDrawing R;
    R.create();
    while(R.update() )
        R.drawRectangle();
    R.close();
    return 0;
}
