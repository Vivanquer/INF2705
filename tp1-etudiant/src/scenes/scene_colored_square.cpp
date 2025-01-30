#include "scene_colored_square.h"

#include "vertices_data.h"

SceneColoredSquare::SceneColoredSquare(Resources& res)
: Scene(res), m_res(res)
{
    // TODO
    // Bind the VAO
    m_coloredSquareVao.bind();
    
    // Bind the vertex buffer
    m_res.coloredSquareReduceBuffer.bind();
    
    // Define position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Define color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ✅ Bind the index buffer
    m_res.coloredSquareReduceIndicesBuffer.bind();

    // Unbind everything
    m_coloredSquareVao.unbind();
    m_res.coloredSquareReduceBuffer.unbind();
    m_res.coloredSquareReduceIndicesBuffer.unbind();
}

void SceneColoredSquare::run(Window& w)
{
    // TODO
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background

    // Use the color shader
    m_res.color.use();

    // Bind the VAO and draw the square using indices
    m_coloredSquareVao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6); // ✅ Draws 6 vertices (2 triangles)
    m_coloredSquareVao.unbind();
}

