#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

Texture2D::Texture2D(const char* path)
{
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);
    if (data == NULL)
        std::cout << "Error loading texture \"" << path << "\": " << stbi_failure_reason() << std::endl;

    // TODO - Chargement de la texture, attention au format des pixels de l'image!

    stbi_image_free(data);
}

Texture2D::~Texture2D()
{
    // TODO
}

void Texture2D::setFiltering(GLenum filteringMode)
{
    // TODO - min et mag filter
}

void Texture2D::setWrap(GLenum wrapMode)
{
    // TODO
}

void Texture2D::enableMipmap()
{
    // TODO - mipmap et filtering correspondant
}

void Texture2D::use()
{
    // TODO
}

