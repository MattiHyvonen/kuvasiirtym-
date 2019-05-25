#include "rectDrawing.h"

int main() {
    rectDrawing R;
    R.create();

    while(R.update() )
        R.drawRectangle();

    return 0;
}
