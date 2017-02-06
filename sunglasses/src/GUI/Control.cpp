// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/Control.h>

namespace sunglasses {
namespace GUI {

Control::Control(glm::ivec2 _position, glm::ivec2 _size, bool _visible, std::initializer_list<Control *> _children) :
        position(_position), size(_size), visible(_visible), state(State::Normal) {
    children.reserve(_children.size());
    for (auto child : _children)
        children.emplace_back(child);
}

void Control::drawAll(glm::ivec2 offset, Renderer2D &renderer) {
    if (visible) {
        draw(offset, renderer);
        drawChildren(offset, renderer);
    }
}

void Control::drawChildren(glm::ivec2 offset, Renderer2D &renderer) {
    for (auto &child : children) {
        child->drawAll(offset + position, renderer);
    }
}

void Control::addChild(Control *control) {
    children.emplace_back(control);
}

} // sunglasses
} // sunglasses
