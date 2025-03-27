#ifndef SCENE_H
#define SCENE_H

#include "window.h"

class Scene
{
public:
    Scene()
    {}
    virtual ~Scene() = default;
    
    virtual void run(Window& w, double dt) = 0;
    
protected:

};

#endif // SCENE_H
