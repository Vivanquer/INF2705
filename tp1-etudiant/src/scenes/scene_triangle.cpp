#include "scene_triangle.h"

#include "vertices_data.h"

SceneTriangle::SceneTriangle(Resources& res)
: Scene(res), m_res(res)
{
    // Initialize the buffer for the triangle vertices
    m_triangleBuffer.allocate(
        GL_ARRAY_BUFFER, 
        sizeof(triVertices), 
        triVertices, 
        GL_STATIC_DRAW
    );

    // Initialize the Vertex Array Object (VAO)
    m_triangleVao.bind();
    m_triangleBuffer.bind();

    // Configure vertex attributes (position at location 0)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_triangleBuffer.unbind();
    m_triangleVao.unbind();
}

void SceneTriangle::run(Window& w)
{
    // Clear the screen with white background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background

    // Use the basic shader program
    m_res.basic.use();

    // Bind the VAO and draw the triangle
    m_triangleVao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_triangleVao.unbind();
}

