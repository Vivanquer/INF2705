#ifndef SCENE_H
#define SCENE_H

#include "resources.h"

#include "window.h"

class Scene
{
public:
    Scene(Resources& res)
    : m_resources(res)
    {}
    virtual ~Scene() = default;
    
    virtual void run(Window& w) = 0;
    
protected:
    Resources& m_resources;

};

#endif // SCENE_H
