#include "model.h"
#include "obj_loader.h"

Model::Model(const char* path)
 : m_drawcall(m_vao, 0, GL_UNSIGNED_INT) 
{
    std::vector<GLfloat> vertexData;
    std::vector<GLuint> indices;
    
    loadObj(path, vertexData, indices);
    
    if (vertexData.empty() || indices.empty()) {
        std::cerr << "Failed to load model from " << path << std::endl;
        return;
    }

    m_vao.bind();

    m_vbo.allocate(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);
    m_vao.specifyAttribute(m_vbo, 0, 3, 5, 0);
    m_vao.specifyAttribute(m_vbo, 1, 2, 5, 3);

    m_ebo.allocate(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    m_drawcall.setCount(static_cast<GLsizei>(indices.size()));
}

void Model::loadObj(const char* path, std::vector<GLfloat>& vertexData, std::vector<GLuint>& indices)
{
	objl::Loader loader;
	bool loadout = loader.LoadFile(path);
	if (!loadout)
	{
		std::cout << "Unable to load model " << path << std::endl;
		return;
	}

	for (size_t i = 0; i < loader.LoadedVertices.size(); i++)
	{
		objl::Vector3 p = loader.LoadedVertices[i].Position;
		vertexData.push_back(p.X);
		vertexData.push_back(p.Y);
		vertexData.push_back(p.Z);
		objl::Vector2 t = loader.LoadedVertices[i].TextureCoordinate;
		vertexData.push_back(t.X);
		vertexData.push_back(t.Y);
	}
	indices = loader.LoadedIndices;
}

void Model::draw()
{
    m_drawcall.draw(); 
}

