// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SYSTEM_H
#define SYSTEM_H

#include <sunglasses/GUI/Window.h>
#include <sunglasses/GUI/Renderer2D.h>

namespace sunglasses {
namespace GUI {

class View;
class ViewController;

/// A GUI containing a window and a content view
class System {
public:
    /// Constructs the GUI with a content view
    System(View *view, Window &_window);

    /// Constructs the GUI with a content view from a view controller
    System(ViewController &viewController, Window &_window);

    /// Updates the GUI elements
    void update();

    /// Draws the GUI and swaps the window's buffers
    void draw();
private:
    /// The window
    Window &window;

    /// The renderer
    Renderer2D renderer;

    /// The main view
    View *contentView;
};

} // namespace
} // namespace

#endif
