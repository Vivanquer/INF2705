#ifndef SCENE_COLORED_TRIANGLE_H
#define SCENE_COLORED_TRIANGLE_H

#include "scene.h"

#include "buffer_object.h"
#include "vertex_array_object.h"
#include "draw_commands.h"

class SceneColoredTriangle : public Scene
{
public:
    SceneColoredTriangle(Resources& res);

    virtual void run(Window& w);
    
private:
    VertexArrayObject m_coloredTriangleVao;
    //DrawArraysCommand m_coloredTriangleDraw;
};

#endif // SCENE_COLORED_TRIANGLE_H
