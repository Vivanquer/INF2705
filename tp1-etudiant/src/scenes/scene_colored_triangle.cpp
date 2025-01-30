#include "scene_colored_triangle.h"

#include "vertices_data.h"

SceneColoredTriangle::SceneColoredTriangle(Resources& res)
: Scene(res), m_res(res)
{
    // TODO
    // Bind the VAO
    m_coloredTriangleVao.bind();
    m_res.coloredTriangleBuffer.bind();

    // ✅ Define position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ✅ Define color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO and VBO
    m_coloredTriangleVao.unbind();
    m_res.coloredTriangleBuffer.unbind();
}

void SceneColoredTriangle::run(Window& w)
{
    // TODO
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background

    // Use the color shader
    m_res.color.use();

    // Bind the VAO and draw the triangle
    m_coloredTriangleVao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_coloredTriangleVao.unbind();
}

