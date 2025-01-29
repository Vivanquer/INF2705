#ifndef SCENE_CUBE_H
#define SCENE_CUBE_H

#include "scene.h"

#include "buffer_object.h"
#include "vertex_array_object.h"
#include "draw_commands.h"

class SceneCube : public Scene
{
public:
    SceneCube(Resources& res);

    virtual void run(Window& w);
    
private:
    float m_rotationAngleDegree;

    BufferObject m_cubeBuffer;
    BufferObject m_cubeIndicesBuffer;
    VertexArrayObject m_cubeVao;
    //DrawElementsCommand m_cubeDraw;
};

#endif // SCENE_CUBE_H
