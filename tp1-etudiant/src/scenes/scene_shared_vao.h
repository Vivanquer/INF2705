#ifndef SCENE_SHARED_VAO_H
#define SCENE_SHARED_VAO_H

#include "scene.h"

#include "buffer_object.h"
#include "vertex_array_object.h"
#include "draw_commands.h"

class SceneSharedVao : public Scene
{
public:
    SceneSharedVao(Resources& res);

    virtual void run(Window& w);
    
    void runTriangle();
    void runSquare();
    
private:
    VertexArrayObject m_sharedVao;
    //DrawArraysCommand m_coloredTriangleSharedDraw;
    //DrawElementsCommand m_coloredSquareSharedDraw;
};

#endif // SCENE_SHARED_VAO_H

