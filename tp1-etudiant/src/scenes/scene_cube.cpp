#include "scene_cube.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vertices_data.h"

SceneCube::SceneCube(Resources& res)
: Scene(res), m_res(res), m_rotationAngleDegree(0.0f)
{
    m_cubeVao.bind();

    m_res.cubeBuffer.bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    m_res.cubeIndicesBuffer.bind();

    m_cubeVao.unbind();
    m_res.cubeBuffer.unbind();
    m_res.cubeIndicesBuffer.unbind();
}

void SceneCube::run(Window& w)
{
    m_rotationAngleDegree += 0.5f;
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    m_res.transform.use();

    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotationAngleDegree), glm::vec3(0.1f, 1.0f, 0.1f));

    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, -2.0f));

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)w.getWidth() / (float)w.getHeight(), 0.1f, 10.0f);

    glm::mat4 mvp = projection * view * model;

    glUniformMatrix4fv(m_res.mvpLocation, 1, GL_FALSE, &mvp[0][0]);

    m_cubeVao.bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);
    m_cubeVao.unbind();
}

