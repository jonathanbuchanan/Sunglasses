// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/Label.h>

namespace sunglasses {
namespace GUI {

Label::Label(glm::ivec2 _position, glm::ivec2 _size, const Drawable::Text &_text) :
        Control(_position, _size), text(_text) {

}

void Label::draw(glm::ivec2 offset, Renderer2D &renderer) {
    text.draw(offset + position, renderer);
}

} // namespace
} // namespace
