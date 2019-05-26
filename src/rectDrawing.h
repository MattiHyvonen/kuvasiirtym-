#include "context.h"
#include <glm/glm.hpp>


//Contains a window and a GL context, and can draw rectangles in it.
class rectDrawing : public context {
    unsigned int vao;
    unsigned int vertexBuffer;
    unsigned int uvBuffer;
    bool created = false;
    
public:
    //Create the window, context and vertex buffers.
    // (see: context::create() )
    // Return false if couldn't create.
    bool create(int width = 640, int height = 512);
    bool isCreated();
    
    bool drawRectangle();
};
