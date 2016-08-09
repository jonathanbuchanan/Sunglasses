// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUI_H
#define GUI_H

#include <sunglasses/GUI/Window.h>
#include <sunglasses/GUI/Renderer.h>

namespace sunglasses {

class View;
class ViewController;

/// A GUI containing a window and a content view
class GUI {
public:
    /// Constructs the GUI with a content view
    GUI(View *view, Window &_window);

    /// Constructs the GUI with a content view from a view controller
    GUI(ViewController &viewController, Window &_window);

    /// Updates the GUI elements
    void update();

    /// Draws the GUI and swaps the window's buffers
    void draw();
private:
    /// The window
    Window &window;

    /// The renderer
    Renderer renderer;

    /// The main view
    View *contentView;
};

} // namespace

#endif
