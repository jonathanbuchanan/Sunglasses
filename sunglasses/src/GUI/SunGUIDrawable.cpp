#include <sunglasses/GUI/SunGUIDrawable.h>

#include <sunglasses/Graphics/SunShader.h>

namespace sunglasses {

SunGUIDrawableSolidColor::SunGUIDrawableSolidColor(glm::vec4 _color) : color(_color) {

}

SunGUIDrawable * SunGUIDrawableSolidColor::copy() const {
    return new SunGUIDrawableSolidColor(*this);
}

void SunGUIDrawableSolidColor::uniforms(SunShader &shader) {
    shader["fillColor"] = color;    
}

} // namespace
