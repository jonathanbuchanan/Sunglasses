#include <sunglasses/Graphics/Texture.h>

#include <SOIL/SOIL.h>

namespace sunglasses {

Image::Image(std::string path) {
    image = SOIL_load_image(path.c_str(), &size.x, &size.y, 0, SOIL_LOAD_RGB);
}

Image::~Image() {
    SOIL_free_image_data(image);
}

Texture::Texture(const Image &image) {
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.size.x, image.size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, image.image);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

} // sunglasses
