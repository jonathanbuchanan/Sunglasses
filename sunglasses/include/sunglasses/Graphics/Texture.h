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
    /// Constructs an image with data from a file
    Image(std::string file);

    /// Destroys the image by releasing the memory containing the data
    ~Image();
private:
    /// The size of the image
    glm::ivec2 size;

    /// The image data
    unsigned char *image;
};

class Shader;

/// A class that contains an OpenGL texture
class Texture {
friend Shader;
public:
    /// Constructs a texture from a bitmap image
    Texture(const Image &image);
private:
    /// The OpenGL texture object
    GLuint texture;
};

} // namespace

#endif
