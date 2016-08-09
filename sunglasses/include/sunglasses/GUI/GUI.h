// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUI_H
#define GUI_H

#include <sunglasses/GUI/GUIWindow.h>
#include <sunglasses/GUI/GUIRenderer.h>

namespace sunglasses {

class GUIView;
class GUIViewController;

/// A GUI containing a window and a content view
class GUI {
public:
    /// Constructs the GUI with a content view
    GUI(GUIView *view, GUIWindow &_window);

    /// Constructs the GUI with a content view from a view controller
    GUI(GUIViewController &viewController, GUIWindow &_window);

    /// Updates the GUI elements
    void update();

    /// Draws the GUI and swaps the window's buffers
    void draw();
private:
    /// The window
    GUIWindow &window;

    /// The renderer
    GUIRenderer renderer;

    /// The main view
    GUIView *contentView;
};

} // namespace

#endif
