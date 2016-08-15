#include <sunglasses/GUI/Drawable.h>

#include <sunglasses/GUI/Renderer.h>

namespace sunglasses {
namespace GUI {

DrawableSolidColor::DrawableSolidColor(glm::vec4 _color) : color(_color) {

}

Drawable * DrawableSolidColor::copy() const {
    return new DrawableSolidColor(*this);
}

void DrawableSolidColor::draw(glm::ivec2 position, glm::ivec2 size,
        Renderer &renderer) {
    renderer.draw(position, size, color);
}





DrawableImage::DrawableImage(Texture &_texture) : texture(_texture) {

}

Drawable * DrawableImage::copy() const {
    return new DrawableImage(*this);
}

void DrawableImage::draw(glm::ivec2 position, glm::ivec2 size,
        Renderer &renderer) {

}

} // namespace
} // namespace
