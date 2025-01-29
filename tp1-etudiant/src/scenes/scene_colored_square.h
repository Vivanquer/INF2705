#ifndef SCENE_COLORED_SQUARE_H
#define SCENE_COLORED_SQUARE_H

#include "scene.h"

#include "buffer_object.h"
#include "vertex_array_object.h"
#include "draw_commands.h"

class SceneColoredSquare : public Scene
{
public:
    SceneColoredSquare(Resources& res);

    virtual void run(Window& w);
    
private:
    BufferObject m_coloredSquareBuffer;
    VertexArrayObject m_coloredSquareVao;
    //DrawArraysCommand m_coloredSquareDraw;
};

#endif // SCENE_COLORED_SQUARE_H
