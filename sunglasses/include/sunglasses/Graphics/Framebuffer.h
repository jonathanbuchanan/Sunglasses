#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <glm/glm.hpp>

#include <GL/glew.h>

#include <sunglasses/Graphics/Texture.h>

namespace sunglasses {

/// A framebuffer attachment for color
template<typename D>
class ColorAttachment {
public:
    /// Constructs the attachment with a size
    ColorAttachment(glm::ivec2 size) : texture(Image<D>(size)) {

    }
private:
    /// The texture attatched to the framebuffer
    Texture texture;
};

/// An object containing buffers to be rendered to
class Framebuffer {
public:
    /// Constructs the framebuffer
    Framebuffer(glm::ivec2 _size);

    /// Destroys the framebuffer
    ~Framebuffer();
private:
    /// The OpenGL framebuffer object
    GLuint framebuffer;

    /// The size of the framebuffer
    glm::ivec2 size;
};

} // namespace

#endif
