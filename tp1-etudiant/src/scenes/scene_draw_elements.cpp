#include "scene_draw_elements.h"

#include "vertices_data.h"

SceneDrawElements::SceneDrawElements(Resources& res)
: Scene(res), m_res(res)
{
    // TODO
   // ✅ Bind the VAO
    m_coloredSquareReduceVao.bind();

    // ✅ Bind the vertex buffer (position + color)
    m_res.coloredSquareBuffer.bind();

    // Define position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Define color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ✅ Bind the index buffer (VERY IMPORTANT)
    m_res.coloredSquareIndicesBuffer.bind(); // Ensure this is bound inside VAO!

    // ✅ Unbind VAO and buffers
    m_coloredSquareReduceVao.unbind();
    m_res.coloredSquareBuffer.unbind();
    m_res.coloredSquareIndicesBuffer.unbind();
}

void SceneDrawElements::run(Window& w)
{
    // TODO
    // ✅ Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background

    // ✅ Use the color shader
    m_res.color.use();

    // ✅ Bind VAO and draw the square
    m_coloredSquareReduceVao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0); // ✅ Must be 6, not 3
    m_coloredSquareReduceVao.unbind();
}


