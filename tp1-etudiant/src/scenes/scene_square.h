#ifndef SCENE_SQUARE_H
#define SCENE_SQUARE_H

#include "scene.h"

#include "buffer_object.h"
#include "vertex_array_object.h"
#include "draw_commands.h"

class SceneSquare : public Scene
{
public:
    SceneSquare(Resources& res);

    virtual void run(Window& w);
    
private:
    Resources& m_res;
    BufferObject m_squareBuffer;
    BufferObject m_squareIndexBuffer;
    VertexArrayObject m_squareVao;
    //DrawArraysCommand m_squareDraw;
};

#endif // SCENE_SQUARE_H
