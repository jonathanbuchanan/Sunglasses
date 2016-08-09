#include <sunglasses/GUI/GUIDrawable.h>

#include <sunglasses/Graphics/Shader.h>

namespace sunglasses {

GUIDrawableSolidColor::GUIDrawableSolidColor(glm::vec4 _color) : color(_color) {

}

GUIDrawable * GUIDrawableSolidColor::copy() const {
    return new GUIDrawableSolidColor(*this);
}

void GUIDrawableSolidColor::uniforms(Shader &shader) {
    shader["fillColor"] = color;    
}

} // namespace
