// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SYSTEM_H
#define SYSTEM_H

#include <functional>

#include <sunglasses/GUI/Renderer2D.h>
#include <sunglasses/GUI/Control.h>

namespace sunglasses {
namespace GUI {

/// A GUI containing a window and a content view
class System {
public:
    /// Constructs the GUI
    System(graphics::Window &_window);

    /// Changes the root control
    void present(Control &control);

    /// Draws the GUI and swaps the window's buffers
    void draw();
private:
    /// Called when the mouse moves
    void mouse_move(glm::ivec2 location);
    Slot<void(System::*)(glm::ivec2), &System::mouse_move> slot_move = {*this};

    /// Called when the left mouse button is pressed
    void mouse_pressLeft(glm::ivec2 mouse);
    Slot<void(System::*)(glm::ivec2), &System::mouse_pressLeft> slot_pressLeft = {*this};

    /// Called when the left mouse button is released
    void mouse_releaseLeft(glm::ivec2 mouse);
    Slot<void(System::*)(glm::ivec2), &System::mouse_releaseLeft> slot_releaseLeft = {*this};

    /// Called when the middle mouse button is pressed
    void mouse_pressMiddle(glm::ivec2 mouse);
    Slot<void(System::*)(glm::ivec2), &System::mouse_pressMiddle> slot_pressMiddle = {*this};

    /// Called when the middle mouse button is released
    void mouse_releaseMiddle(glm::ivec2 mouse);
    Slot<void(System::*)(glm::ivec2), &System::mouse_releaseMiddle> slot_releaseMiddle = {*this};

    /// Called when the right mouse button is pressed
    void mouse_pressRight(glm::ivec2 mouse);
    Slot<void(System::*)(glm::ivec2), &System::mouse_pressRight> slot_pressRight = {*this};

    /// Called when the right mouse button is released
    void mouse_releaseRight(glm::ivec2 mouse);
    Slot<void(System::*)(glm::ivec2), &System::mouse_releaseRight> slot_releaseRight = {*this};

    /// The window
    graphics::Window &window;

    /// The renderer
    Renderer2D renderer;

    /// The root control
    Control *root;
};

} // namespace
} // namespace

#endif
