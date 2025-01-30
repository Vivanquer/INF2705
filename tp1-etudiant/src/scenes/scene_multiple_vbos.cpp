#include "scene_multiple_vbos.h"

#include "vertices_data.h"

SceneMultipleVbos::SceneMultipleVbos(Resources& res)
: Scene(res), m_res(res)
, m_positionX(0.0f), m_positionY(0.0f)
, m_deltaX(0.019f), m_deltaY(0.0128f)
, m_onlyColorTriVertices{ 1.0f, 0.0f, 0.0f,
                           1.0f, 0.0f, 0.0f,
                           1.0f, 0.0f, 0.0f }
{
    // TODO
    // ✅ Allocate position buffer
    m_coloredTrianglePositionBuffer.allocate(
        GL_ARRAY_BUFFER,
        sizeof(triVertices), // Contains 3 vertex positions (x, y)
        triVertices,
        GL_DYNAMIC_DRAW // Since the position will change
    );

    // ✅ Allocate color buffer
    m_coloredTriangleColorBuffer.allocate(
        GL_ARRAY_BUFFER,
        sizeof(m_onlyColorTriVertices), // Contains 3 vertex colors (r, g, b)
        m_onlyColorTriVertices,
        GL_DYNAMIC_DRAW // Colors will change dynamically
    );

    // ✅ Bind VAO and set up attributes
    m_coloredTriangleMultipleVbosVao.bind();

    // ✅ Position attribute (location = 0)
    m_coloredTrianglePositionBuffer.bind();
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ✅ Color attribute (location = 1)
    m_coloredTriangleColorBuffer.bind();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Unbind everything
    m_coloredTriangleMultipleVbosVao.unbind();
    m_coloredTrianglePositionBuffer.unbind();
    m_coloredTriangleColorBuffer.unbind();
}

void SceneMultipleVbos::run(Window& w)
{
    // ✅ Update colors dynamically
    changeRGB(&m_onlyColorTriVertices[0]);
    changeRGB(&m_onlyColorTriVertices[3]);
    changeRGB(&m_onlyColorTriVertices[6]);

    // ✅ Update color buffer data
    m_coloredTriangleColorBuffer.bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_onlyColorTriVertices), m_onlyColorTriVertices);
    m_coloredTriangleColorBuffer.unbind();

    // ✅ Update position dynamically
    GLfloat posData[6] = { m_positionX - 0.5f, m_positionY - 0.5f,
                            m_positionX + 0.5f, m_positionY - 0.5f,
                            m_positionX, m_positionY + 0.5f };

    changePos(posData, m_positionX, m_positionY, m_deltaX, m_deltaY);

    // ✅ Update position buffer data
    m_coloredTrianglePositionBuffer.bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(posData), posData);
    m_coloredTrianglePositionBuffer.unbind();

    // ✅ Clear screen and use shader
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    m_res.color.use();

    // ✅ Draw triangle
    m_coloredTriangleMultipleVbosVao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_coloredTriangleMultipleVbosVao.unbind();
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
