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

enum struct TextureMinification : GLint {
    Nearest = GL_NEAREST,
    Linear = GL_LINEAR,
    NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
    LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
    NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
    LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
};

enum struct TextureMagnification : GLint {
    Nearest = GL_NEAREST,
    Linear = GL_LINEAR
};

enum struct TextureWrap : GLint {
    ClampToEdge = GL_CLAMP_TO_EDGE,
    MirroredRepeat = GL_MIRRORED_REPEAT,
    Repeat = GL_REPEAT
};

/// A class that contains an OpenGL texture
class Texture {
friend Shader;
public:
    /// Constructs a texture from a bitmap image
    Texture(const Image &image,
        TextureMinification _minification = TextureMinification::NearestMipmapLinear,
        TextureMagnification _magnification = TextureMagnification::Linear,
        TextureWrap _SWrap = TextureWrap::Repeat, TextureWrap _TWrap = TextureWrap::Repeat);

    /// Constructs a texture from an image file
    Texture(std::string path,
        TextureMinification _minification = TextureMinification::NearestMipmapLinear,
        TextureMagnification _magnification = TextureMagnification::Linear,
        TextureWrap _SWrap = TextureWrap::Repeat, TextureWrap _TWrap = TextureWrap::Repeat);

    /// Destroys the texture
    ~Texture();
private:
    /// Loads image data into a texture
    void loadImage(const Image &image);

    /// The OpenGL texture object
    GLuint texture;

    /// The minification mode
    TextureMinification minification;

    /// The magnification mode
    TextureMagnification magnification;

    /// The wrapping mode along the S axis
    TextureWrap SWrap;

    /// The wrapping mode along the T axis
    TextureWrap TWrap;
};

} // namespace

#endif
