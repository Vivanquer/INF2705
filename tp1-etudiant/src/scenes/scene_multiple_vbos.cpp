#include "scene_multiple_vbos.h"

#include "vertices_data.h"

SceneMultipleVbos::SceneMultipleVbos(Resources& res)
: Scene(res)
, m_positionX(0.0f), m_positionY(0.0f)
, m_deltaX(0.019f), m_deltaY(0.0128f)
, m_onlyColorTriVertices{ 1.0f, 0.0f, 0.0f,
                           1.0f, 0.0f, 0.0f,
                           1.0f, 0.0f, 0.0f }
{
    // TODO
}

void SceneMultipleVbos::run(Window& w)
{
    changeRGB(&m_onlyColorTriVertices[0]);
    changeRGB(&m_onlyColorTriVertices[3]);
    changeRGB(&m_onlyColorTriVertices[6]);
    // TODO mise a jour de la couleur
    
    // TODO mise a jour de la position
	// Faire attention au nombre de composantes (modifier la méthode au besoin)
	GLfloat* posPtr = nullptr;
    changePos(posPtr, m_positionX, m_positionY, m_deltaX, m_deltaY);

    // TODO dessin
}



void SceneMultipleVbos::changeRGB(GLfloat* color)
{
    unsigned char r = color[0]*255;
    unsigned char g = color[1]*255;
    unsigned char b = color[2]*255;
    
    if(r > 0 && b == 0)
    {
        r--;
        g++;
    }
    if(g > 0 && r == 0)
    {
        g--;
        b++;
    }
    if(b > 0 && g == 0)
    {
        r++;
        b--;
    }
    color[0] = r/255.0f;
    color[1] = g/255.0f;
    color[2] = b/255.0f;
}

void SceneMultipleVbos::changePos(GLfloat* pos, float& cx, float& cy, float& dx, float& dy)
{
    if ((cx < -1 && dx < 0) || (cx > 1 && dx > 0))
        dx = -dx;
    pos[0] += dx;
    pos[6] += dx;
    pos[3] += dx;
    cx += dx;
    if ((cy < -1 && dy < 0) || (cy > 1 && dy > 0))
        dy = -dy;
    pos[1] += dy;
    pos[4] += dy;
    pos[7] += dy;
    cy += dy;
}
