#include <sunglasses/GUI/View3D.h>

namespace sunglasses {
namespace GUI {

void View3D::draw(glm::ivec2 offset, Renderer2D &renderer) {
    framebuffer.activate();
    framebuffer.clear();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glm::vec2 absolute = offset + position;
    background.draw(absolute, size, renderer);
}

} // namespace
} // namespace
