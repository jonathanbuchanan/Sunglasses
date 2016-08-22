// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/Texture.h>

#include <SOIL/SOIL.h>

namespace sunglasses {

Texture::Texture(const Image &image,
        TextureMinification _minification,
        TextureMagnification _magnification,
        TextureWrap _SWrap, TextureWrap _TWrap) :
        minification(_minification), magnification(_magnification),
        SWrap(_SWrap), TWrap(_TWrap) {
    loadImage(image);
}

Texture::Texture(std::string path, Format format,
        TextureMinification _minification,
        TextureMagnification _magnification,
        TextureWrap _SWrap, TextureWrap _TWrap) :
        minification(_minification), magnification(_magnification),
        SWrap(_SWrap), TWrap(_TWrap) {
    glm::ivec2 size;
    unsigned char *imageData = SOIL_load_image(path.c_str(), &size.x, &size.y, 0, SOIL_LOAD_RGBA);
    Image image(size, imageData, format);
    loadImage(image);
    SOIL_free_image_data(imageData);
}

Texture::Texture(std::string path, InternalFormat internalFormat, Format format,
        TextureMinification _minification,
        TextureMagnification _magnification,
        TextureWrap _SWrap, TextureWrap _TWrap) :
        minification(_minification), magnification(_magnification),
        SWrap(_SWrap), TWrap(_TWrap) {
    glm::ivec2 size;
    unsigned char *imageData = SOIL_load_image(path.c_str(), &size.x, &size.y, 0, SOIL_LOAD_RGBA);
    Image image(size, imageData, internalFormat, format);
    loadImage(image);
    SOIL_free_image_data(imageData);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}

void Texture::loadImage(const Image &image) {
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)minification);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)magnification);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)SWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)TWrap);


    glTexImage2D(GL_TEXTURE_2D, 0, image.internalFormat, image.size.x, image.size.y, 0, image.format, image.type, image.data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

GLint Image::deduceInternalFormat(Texture::Format format) {
    switch (format) {
        case Texture::Format::Red:
            return GL_RED;
            break;
        case Texture::Format::RG:
            return GL_RG;
            break;
        case Texture::Format::RGB:
            return GL_RGB;
            break;
        case Texture::Format::BGR:
            return GL_RGB;
            break;
        case Texture::Format::RGBA:
            return GL_RGBA;
            break;
        case Texture::Format::BGRA:
            return GL_RGBA;
            break;
        case Texture::Format::DepthComponent:
            return GL_DEPTH_COMPONENT;
            break;
        case Texture::Format::DepthStencil:
            return GL_DEPTH_STENCIL;
            break;
    }
}

} // sunglasses
