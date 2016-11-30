// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/Texture.h>

#include <SOIL/SOIL.h>

namespace sunglasses {

Texture::Texture(std::string path, Format format,
        TextureMinification _minification,
        TextureMagnification _magnification,
        TextureWrap _SWrap, TextureWrap _TWrap) :
        minification(_minification), magnification(_magnification),
        SWrap(_SWrap), TWrap(_TWrap) {
    glm::ivec2 size;
    unsigned char *imageData = SOIL_load_image(path.c_str(), &size.x, &size.y, 0, SOIL_LOAD_RGBA);
    Image<unsigned char> image(size, imageData, format);
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
    Image<unsigned char> image(size, imageData, internalFormat, format);
    loadImage(image);
    SOIL_free_image_data(imageData);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}

} // sunglasses
