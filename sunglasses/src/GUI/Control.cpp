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

void Control::drawChildren(glm::ivec2 offset, Renderer2D &renderer) {
    for (auto &child : children) {
        child->drawAll(offset + position, renderer);
    }
}

void Control::drawAll(glm::ivec2 offset, Renderer2D &renderer) {
    if (visible) {
        draw(offset, renderer);
        drawChildren(offset, renderer);
    }
}

void Control::updateChildren(glm::ivec2 offset, UpdateInfo updateInfo) {
    for (auto &child : children) {
        child->updateAll(offset + position, updateInfo);
    }
}

void Control::updateAll(glm::ivec2 offset, UpdateInfo updateInfo) {
    State oldState = state;
    updateState(offset, updateInfo);
    if (oldState != state) {
        stateChange(oldState, state);
    }
    update(offset, updateInfo);
    updateChildren(offset, updateInfo);
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

void Control::stateChange(State oldState, State newState) {
    if (oldState != State::Selected && newState == State::Selected)
        signal_selected();
    if (oldState == State::Selected && newState != State::Selected)
        signal_deselected();
}

} // sunglasses
} // sunglasses
