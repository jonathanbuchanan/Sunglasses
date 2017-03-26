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

void Control::mouseMoved(glm::ivec2 offset, glm::ivec2 mouse) {
    // Check to see if the mouse is within the control
    if (contains(offset, mouse)) {
        // If not highlighted already, become highlighted
        if (state == State::Normal)
            highlight();
    } else {
        // If already highlighted, become unhighlighted
        if (state == State::Highlighted)
            unhighlight();
    }

    for (auto &child : children) {
        child->mouseMoved(offset + position, mouse);
    }
}

void Control::mouseLeftPressed(glm::ivec2 offset, glm::ivec2 mouse) {
    // Check to see if the mouse is within the control
    if (contains(offset, mouse)) {
        // Become selected
        select();
    }

    for (auto &child : children) {
        child->mouseLeftPressed(offset + position, mouse);
    }
}

void Control::mouseLeftReleased(glm::ivec2 offset, glm::ivec2 mouse) {
    if (contains(offset, mouse)) {
        unselect(State::Highlighted);
    } else {
        unselect(State::Normal);
    }

    for (auto &child : children) {
        child->mouseLeftReleased(offset + position, mouse);
    }
}

void Control::drawChildren(glm::ivec2 offset, Renderer2D &renderer) {
    for (auto &child : children) {
        child->drawAll(offset + position, renderer);
    }
}

void Control::addChild(Control &control) {
    children.emplace_back(&control);
}

bool Control::contains(glm::ivec2 offset, glm::ivec2 point) {
    if ((offset.x + position.x <= point.x && offset.x + position.x + size.x >= point.x) &&
        (offset.y + position.y <= point.y && offset.y + position.y + size.y >= point.y))
        return true;
    else
        return false;
}

void Control::highlight() {
    state = State::Highlighted;
    signal_highlighted.emit();
}

void Control::unhighlight() {
    state = State::Normal;
    signal_unhighlighted.emit();
}

void Control::select() {
    state = State::Selected;
    signal_selected.emit();
}

void Control::unselect(State next) {
    state = next;
    signal_deselected.emit();
}

} // sunglasses
} // sunglasses
