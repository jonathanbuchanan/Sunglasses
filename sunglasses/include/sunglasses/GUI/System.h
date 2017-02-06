// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SYSTEM_H
#define SYSTEM_H

#include <sunglasses/Graphics/Window.h>
#include <sunglasses/GUI/Renderer2D.h>
#include <sunglasses/GUI/Control.h>

namespace sunglasses {
namespace GUI {

/// A GUI containing a window and a content view
class System {
public:
    /// Constructs the GUI with a content view
    System(graphics::Window &_window);

    /// Updates the GUI elements
    void update();

    /// Draws the GUI and swaps the window's buffers
    void draw();

    /// Adds a child to the root control
    void addChild(Control &control);

    /// Gets the dimensions of the GUI viewing window
    glm::ivec2 getSize() const;
private:
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
