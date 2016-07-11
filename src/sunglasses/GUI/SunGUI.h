// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUI_H
#define SUNGUI_H

#include <sunglasses/GUI/SunGUIWindow.h>

class SunGUIView;
class SunGUIViewController;

/// A GUI containing a window and a content view
class SunGUI {
public:
    /// Constructs the GUI with a content view
    SunGUI(SunGUIView *view, SunGUIWindow &_window);

    /// Constructs the GUI with a content view from a view controller
    SunGUI(SunGUIViewController &viewController, SunGUIWindow &_window);
private:
    /// The window
    SunGUIWindow &window;

    /// The main view
    SunGUIView *contentView;
};

#endif
