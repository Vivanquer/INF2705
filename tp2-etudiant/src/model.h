#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "buffer_object.h"
#include "draw_commands.h"
#include "vertex_array_object.h"

class Model
{
public:
	Model(const char* path);
	void draw();

private:
	void loadObj(const char* path, std::vector<GLfloat>& vertexData, std::vector<GLuint>& indices);

private:
	BufferObject m_vbo, m_ebo;
	VertexArrayObject m_vao;
	DrawElementsCommand m_drawcall;
};

#endif // BUFFER_OBJECT_H
