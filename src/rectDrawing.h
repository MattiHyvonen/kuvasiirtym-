#include "context.h"
#include <glm/glm.hpp>


//Contains a window and a GL context, and can draw rectangles in it.
class rectDrawing : public context {
    unsigned int vao;
    unsigned int vertexBuffer;
    unsigned int uvBuffer;
    bool created = false;
    
public:
    bool create();
    bool isCreated();
    
    bool drawRectangle();
};
