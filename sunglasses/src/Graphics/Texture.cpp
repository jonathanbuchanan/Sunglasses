#include <sunglasses/Graphics/Texture.h>

#include <SOIL/SOIL.h>

namespace sunglasses {

Image::Image(glm::ivec2 _size, const unsigned char *data) : size(_size), image(data) {

}

Texture::Texture(const Image &image,
        TextureMinification _minification,
        TextureMagnification _magnification,
        TextureWrap _SWrap, TextureWrap _TWrap) :
        minification(_minification), magnification(_magnification),
        SWrap(_SWrap), TWrap(_TWrap) {
    loadImage(image);
}

Texture::Texture(std::string path,
        TextureMinification _minification,
        TextureMagnification _magnification,
        TextureWrap _SWrap, TextureWrap _TWrap) :
        minification(_minification), magnification(_magnification),
        SWrap(_SWrap), TWrap(_TWrap) {
    glm::ivec2 size;
    unsigned char *imageData = SOIL_load_image(path.c_str(), &size.x, &size.y, 0, SOIL_LOAD_RGBA);
    Image image(size, imageData);
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


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.size.x, image.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.image);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

} // sunglasses
