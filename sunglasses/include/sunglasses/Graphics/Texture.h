#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <glm/glm.hpp>

#include <GL/glew.h>

namespace sunglasses {

class Texture;

/// A class that contains a bitmap image, which can be loaded into a texture
class Image {
friend Texture;
public:
    /// Constructs an image with a pointer to a byte array and the image size
    /**
     * @warning You are responsible for the memory of the image data.
     * It may be freed after it is used to create a texture.
     */
    Image(glm::ivec2 _size, const unsigned char *data);
private:
    /// The size of the image
    glm::ivec2 size;

    /// The image data
    const unsigned char *image;
};

class Shader;

/// A class that contains an OpenGL texture
class Texture {
friend Shader;
public:
    /// Constructs a texture from a bitmap image
    Texture(const Image &image);

    /// Constructs a texture from an image file
    Texture(std::string path);

    /// Destroys the texture
    ~Texture();
private:
    /// Loads image data into a texture
    void loadImage(const Image &image);

    /// The OpenGL texture object
    GLuint texture;
};

} // namespace

#endif
