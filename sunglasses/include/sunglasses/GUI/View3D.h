#ifndef VIEW3D_H
#define VIEW3D_H

#include <sunglasses/GUI/Control.h>
#include <sunglasses/GUI/Renderer2D.h>

namespace sunglasses {
namespace GUI {

/// A view to a 3D scene
class View3D : public Control {
public:

protected:
    /// Draws the scene
    virtual void draw(glm::ivec2 offset, Renderer2D &renderer);
};

} // namespace
} // namespace

#endif
