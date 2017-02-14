// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SYSTEM_H
#define SYSTEM_H

#include <sunglasses/GUI/Renderer2D.h>
#include <sunglasses/GUI/Control.h>

namespace sunglasses {
namespace GUI {

/// A GUI containing a window and a content view
class System {
public:
    /// Constructs the GUI with a content view
    System(graphics::Window &_window);

    /// Draws the GUI and swaps the window's buffers
    void draw();

    /// Adds a child to the root control
    void addChild(Control &control);

    /// Gets the dimensions of the GUI viewing window
    glm::ivec2 getSize() const;
private:
    /// Called when the mouse moves
    void mouse_move(glm::ivec2 location);
    Slot<void(System::*)(glm::ivec2), &System::mouse_move> slot_move = {*this};

    /// Called when the left mouse button is pressed
    void mouse_pressLeft();
    Slot<void(System::*)(), &System::mouse_pressLeft> slot_pressLeft = {*this};

    /// Called when the left mouse button is released
    void mouse_releaseLeft();
    Slot<void(System::*)(), &System::mouse_releaseLeft> slot_releaseLeft = {*this};

    /// Called when the middle mouse button is pressed
    void mouse_pressMiddle();
    Slot<void(System::*)(), &System::mouse_pressMiddle> slot_pressMiddle = {*this};

    /// Called when the middle mouse button is released
    void mouse_releaseMiddle();
    Slot<void(System::*)(), &System::mouse_releaseMiddle> slot_releaseMiddle = {*this};

    /// Called when the right mouse button is pressed
    void mouse_pressRight();
    Slot<void(System::*)(), &System::mouse_pressRight> slot_pressRight = {*this};

    /// Called when the right mouse button is released
    void mouse_releaseRight();
    Slot<void(System::*)(), &System::mouse_releaseRight> slot_releaseRight = {*this};

    /// The window
    graphics::Window &window;

    /// The renderer
    Renderer2D renderer;

    /// The root control
    class Root : public Control {
    public:
        Root(graphics::Window &window) :
            Control(glm::ivec2(0), window.getSize()) {

        }
    protected:
        virtual void draw(glm::ivec2 offset, Renderer2D &renderer) {

        }
    } root;
};

} // namespace
} // namespace

#endif
