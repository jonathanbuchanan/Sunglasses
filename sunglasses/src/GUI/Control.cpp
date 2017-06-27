// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/Control.h>

namespace sunglasses {
namespace GUI {

Control::Control(glm::ivec2 _position, glm::ivec2 _size, bool _visible) :
        position(_position), size(_size), visible(_visible), state(State::Normal) {
    
}

void Control::close() {
    unselect(State::Normal);
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
}

void Control::mouseLeftPressed(glm::ivec2 offset, glm::ivec2 mouse) {
    // Check to see if the mouse is within the control
    if (contains(offset, mouse)) {
        // Become selected
        select();
    }
}

void Control::mouseLeftReleased(glm::ivec2 offset, glm::ivec2 mouse) {
    if (contains(offset, mouse)) {
        unselect(State::Highlighted);
    } else {
        unselect(State::Normal);
    }
}

bool Control::contains(glm::ivec2 offset, glm::ivec2 point) {
    if ((offset.x + position.x <= point.x && offset.x + position.x + size.x >= point.x) &&
        (offset.y + position.y <= point.y && offset.y + position.y + size.y >= point.y))
        return true;
    else
        return false;
}

void Control::highlight() {
    if (state == State::Highlighted)
        return;
    state = State::Highlighted;
    signal_highlighted.emit();
}

void Control::unhighlight() {
    if (state == State::Normal)
        return;
    state = State::Normal;
    signal_unhighlighted.emit();
}

void Control::select() {
    if (state == State::Selected)
        return;
    state = State::Selected;
    signal_selected.emit();
}

void Control::unselect(State next) {
    if (state == next)
        return;
    state = next;
    signal_deselected.emit();
}

} // sunglasses
} // sunglasses
