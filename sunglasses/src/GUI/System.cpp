// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/GUI/System.h>

#include <sunglasses/GUI/Panel.h>
#include <sunglasses/GUI/Controller.h>

namespace sunglasses {
namespace GUI {

System::System(graphics::Window &_window) :
        window(_window), renderer(_window), root(nullptr) {
    connect(_window.cursor.signal_move, slot_move);
    connect(_window.cursor.signal_pressLeft, slot_pressLeft);
    connect(_window.cursor.signal_releaseLeft, slot_releaseLeft);
    connect(_window.cursor.signal_pressMiddle, slot_pressMiddle);
    connect(_window.cursor.signal_releaseMiddle, slot_releaseMiddle);
    connect(_window.cursor.signal_pressRight, slot_pressRight);
    connect(_window.cursor.signal_releaseRight, slot_releaseRight);
}

void System::present(Control &control) {
    root = &control;
}

void System::draw() {
    // Size the viewport
    window.sizeViewportToWindow();

    // Clear the window
    window.clear();

    // Draw the GUI
    if (root != nullptr)
        root->drawAll(glm::ivec2(0), renderer);

    // Swap the window's buffers
    window.swapBuffers();
}


void System::mouse_move(glm::ivec2 location) {
    if (root != nullptr)
        root->mouseMoved(glm::ivec2(0), location);
}

void System::mouse_pressLeft(glm::ivec2 mouse) {
    if (root != nullptr)
        root->mouseLeftPressed(glm::ivec2(0), mouse);
}

void System::mouse_releaseLeft(glm::ivec2 mouse) {
    if (root != nullptr)
        root->mouseLeftReleased(glm::ivec2(0), mouse);
}

void System::mouse_pressMiddle(glm::ivec2 mouse) {

}

void System::mouse_releaseMiddle(glm::ivec2 mouse) {

}

void System::mouse_pressRight(glm::ivec2 mouse) {

}

void System::mouse_releaseRight(glm::ivec2 mouse) {

}

} // namespace
} // namespace
