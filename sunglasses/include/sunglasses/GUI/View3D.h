#ifndef VIEW3D_H
#define VIEW3D_H

#include <sunglasses/GUI/Control.h>
#include <sunglasses/GUI/Renderer2D.h>
#include <sunglasses/Graphics/Framebuffer.h>
#include <sunglasses/GUI/Drawable.h>

namespace sunglasses {
namespace GUI {

/// A view to a 3D scene
class View3D : public Control {
public:
    /// Constructs the view
    View3D(glm::ivec2 position, glm::ivec2 size) : Control(position, size), framebuffer(size),
        background(framebuffer.getAttachment<0>()) {

    }
protected:
    /// Draws the scene
    virtual void draw(glm::ivec2 offset, Renderer2D &renderer);
private:
    /// The framebuffer to be drawed on
    Framebuffer<ColorAttachment> framebuffer;

    /// The background
    Drawable::Image background;   
};

} // namespace
} // namespace

#endif
