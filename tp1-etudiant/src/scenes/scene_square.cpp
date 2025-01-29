#include "scene_square.h"

#include "vertices_data.h"

SceneSquare::SceneSquare(Resources& res)
: Scene(res), m_res(res)
{
    // Allocate buffer for square vertices
    m_squareBuffer.allocate(
        GL_ARRAY_BUFFER,
        sizeof(squareVertices),
        squareVertices,
        GL_STATIC_DRAW
    );


    // Configure VAO
    m_squareVao.bind();
    m_squareBuffer.bind();

    // Set vertex attributes (position at location 0)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_squareVao.unbind();
    m_squareBuffer.unbind();

    // Optional: Set up a DrawElementsCommand
    // m_squareDraw = DrawElementsCommand(m_squareVao, 6, GL_UNSIGNED_BYTE);
}

void SceneSquare::run(Window& w)
{
    // Clear the screen with a white background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background

    // Use the basic shader program
    m_res.basic.use();

    // Bind the VAO and draw the square
    m_squareVao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0); // Use the index buffer
    m_squareVao.unbind();

    // Optional: Use the encapsulated draw command
    // m_squareDraw.draw();
}
