#include <sunglasses/GUI/Drawable.h>

#include <sunglasses/Graphics/Shader.h>

namespace sunglasses {
namespace GUI {

DrawableSolidColor::DrawableSolidColor(glm::vec4 _color) : color(_color) {

}

Drawable * DrawableSolidColor::copy() const {
    return new DrawableSolidColor(*this);
}

void DrawableSolidColor::uniforms(sunglasses::Shader &shader) {
    shader["fillColor"] = color;    
}

} // namespace
} // namespace
