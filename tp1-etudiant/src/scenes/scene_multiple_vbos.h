#ifndef SCENE_MULTIPLE_VBOS_H
#define SCENE_MULTIPLE_VBOS_H

#include "scene.h"

#include "buffer_object.h"
#include "vertex_array_object.h"
#include "draw_commands.h"

class SceneMultipleVbos : public Scene
{
public:
    SceneMultipleVbos(Resources& res);

    virtual void run(Window& w);

private:
    void changeRGB(GLfloat* color);
    void changePos(GLfloat* pos, float& cx, float& cy, float& dx, float& dy);    

private:
    float m_positionX, m_positionY;
    float m_deltaX, m_deltaY;
    GLfloat m_onlyColorTriVertices[9];

    BufferObject m_coloredTrianglePositionBuffer;
    BufferObject m_coloredTriangleColorBuffer;
    VertexArrayObject m_coloredTriangleMultipleVbosVao;
    //DrawArraysCommand m_coloredTriangleMultipleVbosDraw;
};

#endif // SCENE_MULTIPLE_VBOS_H
