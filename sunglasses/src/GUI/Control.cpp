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

void Control::updateAll(glm::ivec2 offset, UpdateInfo updateInfo) {
    if (visible) {
        update(offset, updateInfo);
        updateChildren(offset, updateInfo);
    }
}

void Control::updateChildren(glm::ivec2 offset, UpdateInfo updateInfo) {
    for (auto &child : children) {
        child->updateAll(offset + position, updateInfo);
    }
}

void Control::update(glm::ivec2 offset, UpdateInfo updateInfo) {
    State oldState = state;
    // Update the state
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
    // Emit a signal depending on state change
    switch (oldState) {
    case State::Normal:
        switch (state) {
            case State::Normal:
                // No Change
                break;
            case State::Highlighted:
                signal_highlighted();
                break;
            case State::Selected:
                signal_selected();
                break;
        }
        break;
    case State::Highlighted:
        switch (state) {
            case State::Normal:
                signal_unhighlighted();
                break;
            case State::Highlighted:
                // No Change
                break;
            case State::Selected:
                signal_selected();
                break;
        }
        break;
    case State::Selected:
        switch (state) {
            case State::Normal:
                signal_deselected();
                break;
            case State::Highlighted:
                signal_highlighted();
                break;
            case State::Selected:
                // No Change
                break;
        }
        break;
    }
}

void Control::addChild(Control *control) {
    children.emplace_back(control);
}

} // sunglasses
} // sunglasses
