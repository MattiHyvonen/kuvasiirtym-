#include "context.h"
#include <glm/glm.hpp>

class rectDrawing : public context {
    unsigned int vao;
    unsigned int vertexBuffer;
public:
    //Create context (see: context::create()) and vertex buffers.
    // Return false if couldn't create.
    bool create(int width = 640, int height = 512);
    bool drawRectangle();
};
