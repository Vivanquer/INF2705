#ifndef SCENE_DRAW_ELEMENTS_H
#define SCENE_DRAW_ELEMENTS_H

#include "scene.h"

#include "buffer_object.h"
#include "vertex_array_object.h"
#include "draw_commands.h"

class SceneDrawElements : public Scene
{
public:
    SceneDrawElements(Resources& res);

    virtual void run(Window& w);
    
private:
    VertexArrayObject m_coloredSquareReduceVao;
    //DrawElementsCommand m_coloredSquareReduceDraw;
};

#endif // SCENE_DRAW_ELEMENTS_H
