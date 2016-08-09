#include <sunglasses/GUI/Drawable.h>

#include <sunglasses/Graphics/Shader.h>

namespace sunglasses {

DrawableSolidColor::DrawableSolidColor(glm::vec4 _color) : color(_color) {

}

Drawable * DrawableSolidColor::copy() const {
    return new DrawableSolidColor(*this);
}

void DrawableSolidColor::uniforms(Shader &shader) {
    shader["fillColor"] = color;    
}

} // namespace
