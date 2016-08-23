// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/Panel.h>

#include <sunglasses/GUI/Renderer2D.h>
#include <sunglasses/GUI/Window.h>

namespace sunglasses {
namespace GUI {

Panel::Panel(glm::ivec2 _position, glm::ivec2 _size,
        const Drawable &_drawable, bool _visible) :
        Control(_position, _size), drawable(_drawable.copy()),
        visible(_visible) {

}

void Panel::draw(glm::ivec2 offset, Renderer2D &renderer) {
    glm::ivec2 absolute = offset + position;
    drawable->draw(absolute, size, renderer);
}

} // namespace
} // namespace
