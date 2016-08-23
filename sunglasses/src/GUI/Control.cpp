// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/Control.h>

namespace sunglasses {
namespace GUI {

Control::Control(glm::ivec2 _position, glm::ivec2 _size) :
        position(_position), size(_size), state(State::Normal) {

}

Control::Control(glm::ivec2 _position, glm::ivec2 _size, std::initializer_list<Control *> _children) :
        position(_position), size(_size), state(State::Normal) {
    children.reserve(_children.size());
    for (auto child : _children)
        children.emplace_back(child);
}

void Control::drawChildren(glm::ivec2 offset, Renderer2D &renderer) {
    for (auto &child : children) {
        child->draw(offset + position, renderer);
        child->drawChildren(offset + position, renderer);
    }
}

void Control::update(glm::ivec2 offset, UpdateInfo updateInfo) {
    updateState(offset, updateInfo);
}

void Control::updateChildren(glm::ivec2 offset, UpdateInfo updateInfo) {
    for (auto &child : children) {
        child->update(offset + position, updateInfo);
        child->updateChildren(offset + position, updateInfo);
    }
}

void Control::addChild(Control *control) {
    children.emplace_back(control);
}

void Control::updateState(glm::ivec2 offset, UpdateInfo updateInfo) {
    glm::ivec2 absolute = offset + (glm::ivec2)position;
    glm::ivec2 cursor = updateInfo.cursor;
    if ((absolute.x <= cursor.x && cursor.x <= absolute.x + size.x) &&
        (absolute.y <= cursor.y && cursor.y <= absolute.y + size.y)) {
        if (updateInfo.leftMouseButton == WindowButtonState::Pressed)
            state = State::Selected;
        else
            state = State::Highlighted;
    } else {
        state = State::Normal;
    }
}

} // sunglasses
} // sunglasses
