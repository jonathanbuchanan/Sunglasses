// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/System.h>

#include <sunglasses/GUI/Panel.h>
#include <sunglasses/GUI/Controller.h>

namespace sunglasses {
namespace GUI {

System::System(graphics::Window &_window) :
        root(_window), window(_window),
        renderer(_window) {
    connect(_window.cursor.signal_move, slot_move);
    connect(_window.cursor.signal_pressLeft, slot_pressLeft);
    connect(_window.cursor.signal_releaseLeft, slot_releaseLeft);
    connect(_window.cursor.signal_pressMiddle, slot_pressMiddle);
    connect(_window.cursor.signal_releaseMiddle, slot_releaseMiddle);
    connect(_window.cursor.signal_pressRight, slot_pressRight);
    connect(_window.cursor.signal_releaseRight, slot_releaseRight);
}

void System::draw() {
    // Size the viewport
    window.sizeViewportToWindow();

    // Clear the window
    window.clear();

    // Draw the GUI
    root.drawAll(glm::ivec2(0), renderer);

    // Swap the window's buffers
    window.swapBuffers();
}

void System::addChild(Control &control) {
    root.addChild(&control);
}


glm::ivec2 System::getSize() const {
    return window.getSize();
}



void System::mouse_move(glm::ivec2 location) {

}

void System::mouse_pressLeft() {

}

void System::mouse_releaseLeft() {

}

void System::mouse_pressMiddle() {

}

void System::mouse_releaseMiddle() {

}

void System::mouse_pressRight() {

}

void System::mouse_releaseRight() {

}

} // namespace
} // namespace
