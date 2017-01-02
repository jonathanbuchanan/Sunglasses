// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/Drawable.h>

#include <sunglasses/GUI/Renderer2D.h>

namespace sunglasses {
namespace GUI {
namespace Drawable {

Color::Color(glm::vec4 _color) : color(_color) {

}

Color & Color::operator=(glm::vec4 _color) {
    color = _color;
    return *this;
}

void Color::draw(glm::ivec2 position, glm::ivec2 size,
        Renderer2D &renderer) {
    renderer.draw(position, size, color);
}





Image::Image(const graphics::Texture &_texture) : texture(_texture) {

}

void Image::draw(glm::ivec2 position, glm::ivec2 size,
        Renderer2D &renderer) {
    renderer.draw(position, size, texture);
}




Text::Text(std::string _text, glm::vec4 _color, Font &_font) :
        text(_text), color(_color), font(_font) {

}

void Text::draw(glm::ivec2 position, Renderer2D &renderer) {
    renderer.draw(position, text, color, font);
}

} // namespace
} // namespace
} // namespace
