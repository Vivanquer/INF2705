#ifndef TEXTURES_H
#define TEXTURES_H


#include <GL/glew.h>

class Texture2D
{
public:
	Texture2D(const char* path);
	~Texture2D();
	
	void setFiltering(GLenum filteringMode);
	void setWrap(GLenum wrapMode);

	void enableMipmap();

	void use(int i = 0);

private:
	GLuint m_id;
};


#endif // TEXTURES
