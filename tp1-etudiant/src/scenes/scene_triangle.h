#ifndef SCENE_TRIANGLE_H
#define SCENE_TRIANGLE_H

#include "scene.h"

#include "buffer_object.h"
#include "vertex_array_object.h"
#include "draw_commands.h"

class SceneTriangle : public Scene
{
public:
    SceneTriangle(Resources& res);

    virtual void run(Window& w);
    
private:
    Resources& m_res;
    BufferObject m_triangleBuffer;
    VertexArrayObject m_triangleVao;
    //DrawArraysCommand m_triangleDraw;
};

#endif // SCENE_TRIANGLE_H
