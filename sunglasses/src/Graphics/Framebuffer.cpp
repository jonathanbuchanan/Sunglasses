#include <sunglasses/Graphics/Framebuffer.h>

namespace sunglasses {

Framebuffer::Framebuffer(glm::ivec2 _size) : size(_size) {
    glGenFramebuffers(1, &framebuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        // ERROR!
    }
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &framebuffer);
}

} // namespace
