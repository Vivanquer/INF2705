#include "scene_shared_vao.h"

#include "vertices_data.h"

SceneSharedVao::SceneSharedVao(Resources& res)
: Scene(res), m_res(res)
{
    m_sharedVao.bind();

    m_res.coloredSharedBuffer.bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    m_res.coloredSquareIndicesBuffer.bind();

    m_sharedVao.unbind();
    m_res.coloredSharedBuffer.unbind();
    m_res.coloredSquareIndicesBuffer.unbind();
}

void SceneSharedVao::run(Window& w)
{
    // Exceptionnellement, cette méthode n'est pas utilisée
    
}
    
void SceneSharedVao::runTriangle()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    m_res.color.use();

    m_sharedVao.bind();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_sharedVao.unbind();
}

void SceneSharedVao::runSquare()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    m_res.color.use();

    m_sharedVao.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    m_sharedVao.unbind();
}


